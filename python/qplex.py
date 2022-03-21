import sys
import re
    # <program> :                           # <params> 
      # <expression>                          # <name>
      # <assignment>                          # <name> , <params>
      # while ( <name> )                                                  
      # <comment>                           # <args>
                                              # <traditionalargs>
    # <comment>                               # <fancyargs>
      # //.*$                                                             
      # --- .* ---                          # <traditionalargs>
                                              # ( <expression> )
    # <expression> :                          # ( <expression> , <args> )
      # <fn>                                                              
      # <name> <args>                       # <fancyargs>
      # <name>                                # <block>
                                              # <block> <args>
    # <fn>                                    # <args> <block>
      # fn <name> ( <params> ) <block>
      # fn ( <params> ) <block>
      # <params> : <block>
    
    # <name>
      # [A-Za-z_][A-Za-z_0-9]*

class Debugger:
  def __init__(self, active=True):
    self.indentlevel = 0
    self.active = active 

  def install(self, prog):
    self.prog = prog
    self.source = str(prog.read(), 'ascii')
    prog.seek(0)

  def step(self):
    pass

  def msg(self, c, m=None):
    if not self.active:
      return
    if m==None:
      m = c
      c = "none"
    cs = {'none': '0', 'red': '37;41', 'green': '37;42', 'blue': '37;44', 'yellow': '30;43'}[c] 
    print(self.indent(), end="")
    print(f"\u001b[{cs}m{str(m).upper()}\u001b[0m")

  def indent(self, delta=0):
    self.indentlevel += delta
    return self.indentlevel*"    "

  def short_report(self):
    i = self.prog.tell()
    s = self.source.replace("\n", "$")+" "
    return f"\t\t\t{i}/{len(s)}\t\t{s[:i]}[{s[i]}]{s[i+1:]}"

  def trace(self, fn):
    if not self.active:
      return fn
    def R(*k,**n):
      def filterarg(x):
        s = f'"{x}"' 
        s = s.replace("\n", "\\n")
        if "BufferedReader" in s:
          s = "" 
        return s
      sname = fn.__name__.upper()
      self.msg('none', "START " + sname + " ".join([filterarg(x) for x in k if x]) + f"{self.short_report()}")
      self.indent(1)
      ret = fn(*k,**n)
      self.indent(-1)
      if ret == None:
        self.msg('none',"ABORT " + sname + " ".join([filterarg(x) for x in k]) + f"{self.short_report()}")
      else:
        self.msg('none',"END " + sname + " ".join([filterarg(x) for x in k]) + f"{self.short_report()}")
      return ret
    return R

mem = {"print":print}
d = Debugger()
L = []

@d.trace
def getChar(f, c):
  if str(f.read(1), 'ascii') == c:
    return True
  else:
    f.seek(-1,1)
    return None

@d.trace
def pushLocation(f):
  d.msg(f"Saving {f.tell()}")
  L.append(f.tell())

@d.trace
def popLocation(f):
  global L
  d.msg(f"Restoring {L[-1]}")
  f.seek(L[-1])
  L = L[:-1]

@d.trace
def getName(f):
  name = str(f.read(1), 'ascii')
  if re.match("[A-Za-z_]", name):
    while re.match("[A-Za-z0-9_]*$", name):
      b = f.read(1)
      if not b:
        # EOF
        break
      name += str(b, 'ascii')
    # return 1 erroneous char
    f.seek(-1,1)
    return name[:-1]
  else:
    # did not find a name
    f.seek(-1,1)
    return

@d.trace
def getBlock(f):
  getChar(f, '{')
  # store program
  getChar(f, '}')

@d.trace
def performFunctionDefinition(f):
  moreArgs = True
  args = []
  pushLocation(f)
  while moreArgs:
    args.append(getName(f))
    moreArgs = getChar(f, ',')

  # TODO conditional
  popLocation(f)

  getChar(f, ':')
  getBlock(f)

@d.trace
def performLookup(f):
  v = getName(f)
  if not v:
    return None
  d.msg("blue", f"function {v}")
  if not v in mem.keys():
    print(f"QPLEX ERROR: {v} is not defined.")
    exit(1)
  return mem[v]

@d.trace
def performFunctionCall(f):
  d.msg("green", "TARGET AREA")
  fn = performLookup(f)
  d.msg("blue", str(fn) or "None")
  if not fn:
    return None
  while not getChar(f, "\n") and not getChar(f, ";"):
    getChar(f, "(")
    arg0 = performExpression(f)
    while arg0 and getChar(f, ","):
      performExpression(f)
    getChar(f, ")")
    d.msg("yellow", "HELLO THERE")
    getBlock(f)
  d.msg("blue", f"I intend to call {fn} with arg {arg0}")
  fn(arg0)
  return True
  #executeProgram(mem[fn])

@d.trace
def getString(f):
  if not getChar(f, '"'):
    return None
  o = ""
  while re.match("[^\"]", str(f.peek(1), 'ascii')):
    o += str(f.read(1), 'ascii')
  if not getChar(f, '"'):
    print("QPLEX SYNTAX ERROR (string EOF)")
  return o

@d.trace
def performExpression(f):
  v = getString(f)
  if (v!=None): return v
  v = performFunctionDefinition(f)
  if (v!=None): return v
  v = performFunctionCall(f)
  if (v!=None): return v
  v = performLookup(f)
  if (v!=None): return v

def getOperator(f):
  if getChar(f, '+'):
    return '+'
  if getChar(f, '=') and not getChar(f, '='):
    return '='
  if getChar(f, '=') and getChar(f, '='):
    return '=='

@d.trace
def performExpressOp(f):
  A = performExpression(f) # A is a value
  op = getOperator(f)
  if op:
    B = performExpressOp(f) # B is a value or operation
    print(f"you should do {op} to {A} and {B}")

@d.trace
def performWhile(f):
  pass

@d.trace
def performSkipComment(f):
  pass

@d.trace
def executeProgram(f):
  # if there is any file left
  while f.peek(1):
    # each of these functions
    # will check if this kind
    # of sequence is under the
    # file pointer and perform
    # the execution if is
    performExpressOp(f)
    performWhile(f)
    performSkipComment(f)
  return 1

if sys.argv[1:2]:
  with open(sys.argv[1], 'rb') as programfile:
    d.install(programfile)
    executeProgram(programfile)
    # if there is any file left
    if programfile.read(1):
      raise Exception("Incomplete Program Execution")

    # <block>
      # { <program> }
      # <expression>

    # <assignment> :
      # <advname> = <expression>

    # <advname>
      # <name>
      # <name> . <advname>
      # <name> \[ "<string>" \]
      # FILE ( "<string>" )

    # <string>
      # [^"] '' -> "   ' ' -> ''  '  ' -> ' '
