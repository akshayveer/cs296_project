#!/bin/bash
cd cs296_base_code; 
make distclean; 
cd ../
git add *
git commit -m $1  
