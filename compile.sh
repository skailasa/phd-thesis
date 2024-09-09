#!/bin/bash
xelatex thesis.tex
bibtex thesis
makeglossaries thesis
# pdflatex main.tex
xelatex thesis.tex