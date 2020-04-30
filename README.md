# SearchEngine
A search engine optimized for news blogs

A guide on how the project functions: 
1. cpp_backend folder:

First, a single file from all-the-news dataset (not provided in this uploaded file) is broken into separate files (50k  records from one file separated into 50k separate files) using the workbook_generator.cpp code file.

The dataset_modifier.cpp is run for every previously generated file, to eliminate useless columns and neaten up the format of each record.

The forward_index.cpp code is run on the modified files. The first 4 lines of the modified are treated as fancy hits and the text is treated as plain. This generated 4 forward indexes (seperated based on wordID mod) and a lexicon file.

The inverted_index.cpp file is run on the forward index files and generated 4 inverted index barrels along with a short inverted index barrel dedicated for fancy hits.

2. java_frontend folder:

RunPage.java file is main file which starts the project frontend. It loads the four inverted indexes, the short inverted index, and the lexicon (by using ReadfromFile.java) and provides the UI (by using SearchPage.java) for searching. You can either search a query on this page or head over to content addition page.

ResultsPage.java displays the results of the query once search is hit (by using Searching.java, sortFinal.java, and multiWord.java)

AdditionPage.java provides UI for dynamic content addition (uses ReadfromFile.java for content addition). It adds the specified files into our dataset by parsing them and updating lexicon, all four inverted index and short index maps.

A sample dataset of first 1000 modified docs is provided to test out the code.
