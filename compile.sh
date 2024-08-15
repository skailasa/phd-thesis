#!/bin/bash
pdflatex thesis.tex
bibtex thesis
makeglossaries thesis
# pdflatex main.tex
pdflatex thesis.tex