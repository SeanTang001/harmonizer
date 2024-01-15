# Importing Libraries 
import serial 
import time 
import subprocess
import os


os.system('~/MATLAB/R2023a/bin/matlab -nodisplay -nosplash -nodesktop -r '
+'"run(\'/home/seantang001/Desktop/harmonizer/auto_transcriber/music_extractor.m\');exit;"')

os.system('python3 ./mat_to_ly.py')

os.system('lilypond ./output.ly')

os.system('timidity ./output.midi')

