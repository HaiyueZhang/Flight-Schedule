# Open Flights Final Project

- **Haiyue Zhang** (_haiyuez2_)   **Shitao Shi** (_shi40_)    **Raymond Wu** (_haozhen6_)

## Github Organization
- This [link](https://drive.google.com/drive/u/0/folders/1Mn-59EoyDS9gIRRMF31z4cxj8FdZx35_) is to our video demo.
- Our primary file structure should look like this:
```
dir/
    data/
        input.dat
        input_detail.dat
        main.ipynb
        main.py
    documents/
        Contract.md
        Proposal.md
        log.md
        results.md
    src/
        Airport.cpp
        Airport.h
        BFS.cpp
        BFS.h
        Interaction.h
        interaction.cpp
        readFile.cpp
        readFile.h
    tests/
        testdata1.dat
        tests.cpp
    Makefile
    main.cpp
```
  - `data` stores raw data, cleaned data and data processing routine. 
  - `src` contains all source code.
  - `documents` includes our [contract](documents/Contract.md), [proposal](documents/Proposal.md), [log](documents/log.md) and [results](documents/results.md).
  - `tests` contains all tests cases.
## Running Instructions

### Build and Run Main
```
$ make main && ./main
```

### Build and Run Test
```
$ make test && ./test
```

Please see our [video demo](https://drive.google.com/drive/u/0/folders/1Mn-59EoyDS9gIRRMF31z4cxj8FdZx35_) for running example.
