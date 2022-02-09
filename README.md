# FEUP-AED-PROJ2

Second project for the AED course unit at FEUP.

The objective of the project was to create a "planner" for routes in the STCP bus network.

## Building

This project uses [cmake](https://cmake.org/). Assuming it's installed and properly setup, simply run `cmake -S . -B build` in this project's directory to generate the build system, then `cmake --build build` to actually build the project.

This will generate two binaries in the `build` directory, `aed_proj2` and `aed_proj2_no_ansi`, one that uses [ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code) and one that doesn't.

Additionally, documentation will also be generated in the `docs` folder. Run `git submodule init` then `git submodule update` then build again to get the documentation website looking fancy.

## Running

Simply run the executable generated in the last section.

## Unit info

* **Name**: Algoritmos e Estruturas de Dados (Algorithms and Data Structures)
* **Date**: Year 2, Semester 1, 2021/22
* **See also**: [feup-aed-proj1](https://github.com/toni-santos/aed-proj1-2021)
* [**More info**](https://sigarra.up.pt/feup/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=484404)

## Disclaimer

This repository is for archival and educational purposes only.

If you don't understand some part of the code or anything else in this repo, feel free to ask (although I may not understand it myself anymore).

Keep in mind that this repo is public. If you copy any code and use it in your school projects you may be flagged for plagiarism by automated tools.