from subprocess import check_output as call
from subprocess import check_call as ccall
from subprocess import STDOUT
import os

_bailed = False

def bail():
  global _bailed
  _bailed = True

def abrT(r):
  o = ""
  for line in r.split("\n"):
    if "Traceback" in line:
      o += "Traceback:\n\n"
    elif "File" in line:
      a = line[line.find(", ")+2:] + "\n"
      a = a.replace(", in <module>", "")
      o += "  " + a
    elif ":" in line:
      o += "  " + line.split(": ")[0] + ":  " + line.split(": ")[1] + "\n"
    else:
      o += line + "\n"
  return o[:-1]

def test(prog=None, expected=""):
  print(f" === {prog or 'MAIN MODULE'} === ")
  if _bailed:
    return
  if prog and not os.path.exists('tests/'+prog):
    expected = "FILE EXISTS"
    result = "IT DOES NOT"
  else:
    try:
      # i think windows is > NUL or something
      if prog:
        result = str(call("python3 qplex.py tests/"+prog+"; echo -n", shell=1, stderr=STDOUT), 'utf-8')
        resultc = 0
        try:
          ccall("python3 qplex.py tests/"+prog, shell=1, stderr=DEVNULL)
        except:
          resultc = 1
      else:
        result = str(call("python3 qplex.py; echo -n", shell=1, stderr=STDOUT), 'utf-8')
      result = f'{result}'
      expected = f'{expected}'
    except Exception as ex:
      result = ex
  if expected==result:
    print("Passed!")
    return True
  elif not resultc:
    print(f"EXPECTED: \"{expected}\"\nRESULT: \"{result}\"\n")
  else:
    print(abrT(result))

# test the module, then test the features
test("helloworld.qpl", "Hello, World!") or bail()
test("assignmentAndLookup.qpl") or bail()
test("functiondefAndCall.qpl") or bail()
test("functiondef.qpl") or bail()
test("helloComments.qpl") or bail()
test("moreComments.qpl") or bail()
test("objects.qpl") or bail()
test("operators.qpl") or bail()
