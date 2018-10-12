#!/bin/bash

cp sample sample.abs
./abs2rel sample.abs sample.rel

compress sample.abs
compress sample.rel

