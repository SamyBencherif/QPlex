import sys
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

mem = {}

def getChar(f, c):
  pass

def getName(f):
  pass

def getBlock(f):
  getChar(f, '{')
  # store program
  getChar(f, '}')

def performFunctionDefinition(f):
  moreArgs = True
  args = []
  while moreArgs:
    args.append(getName(f))
    moreArgs = getChar(f, ',')
  getChar(f, ':')
  getBlock(f)

def performLookup(f):
  v = getName()
  return m[v]

def performFunctionCall(f):
  fn = performLookup(f)
  executeProgram(mem[fn]

def performOperation(f):
  if f.read(1) == '(':
    performExpression()
    f.read(1) # )
  else:
    f.seek(-1,1)
  A = performExpression()
  f.read(1) # operator symbol
  B = performExpression()
  return A+B

def performExpression(f):
  v = performFunctionDefinition(f)
  if (v): return v
  v = performFunctionCall(f)
  if (v): return v
  v = performLookup(f)
  if (v): return v
  # this one should be last
  v = performOperation(f)
  if (v): return v    

def executeProgram(f):
  # if there is any file left
  while f.read(1):
    # undo byte read
    f.seek(-1,1)

    # each of these functions
    # will check if this kind
    # of sequence is under the
    # file pointer and perform
    # the execution if is
    performExpression(f)
    performAssignment(f)
    performWhile(f)
    performSkipComment(f)

if sys.argv[1:2]:
  with open(sys.argv[1], 'rb') as programfile:
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
