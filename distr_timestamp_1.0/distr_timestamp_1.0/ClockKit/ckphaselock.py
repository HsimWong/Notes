#!/usr/bin/python

import time
import clockkit

clockkit.ckInitialize

while 1:
  if clockkit.ckInSync():
    print "offset=", clockkit.ckOffset(), ", timestamp=", clockkit.ckTimeAsString()
  else:
    print "offset: OUT OF SYNC"
  time.sleep(1)
