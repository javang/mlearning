import sys
import tempfile
import os

class ErrorColor:
 
   def buffered_spawn( self, sh, escape, cmd, args, env ):
       """
           Print errors in bold red
       """
       sys.stderr.flush()
       sys.stdout.flush()
       olderr = sys.stderr
       oldout = sys.stdout
       try:
 
           (outfd, fn) = tempfile.mkstemp()
           fout = os.fdopen(outfd, 'r')
           (errfd, fn) = tempfile.mkstemp()
           ferr = os.fdopen(errfd, 'r')
           try:
               ret = self.env['PSPAWN']( sh, escape, cmd, args, env, fout, ferr)
           finally:
               ferr.seek(0)
               fout.seek(0)
               err = ferr.read()
               out = fout.read()
               err = '\033[01;91m'+err+'\033[0m'
               sys.stderr.write(err)
       finally:
           sys.stderr = olderr
           sys.stdout = oldout
       return ret
