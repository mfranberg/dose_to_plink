# dose_to_plink

This program transposes imputation files as outputted from the minimac software. It trades memory for speed in the sense that everything is read into memory. This makes it unsuitable for big imputation files, e.g. for whole chromosomes. Each dosage is stored efficiently as a fixed point number and will therefore use 2 bytes per dose. The amount of memory required can then be approximated by ( nsamples * nsnps * 2 ) / 10^9 GB.

It can currently handle:
* Both .prob and .dose files.
* Read both zipped and unzipped dosages.
* Outputting the transposed dosages in a specific order (to make merging of chunks easy).
* And change the names of the individuals.

## Building

The dose_to_plink program uses cmake for building, and can easily be built by:

    mkdir build
    cd build
    cmake ../
    make

One of the supporting libraries requires some headers from boost, so you might need to set -DCMAKE_CXX_FLAGS appropirately when running cmake if you only have a local installation of boost. You do not need to build boost, only tell cmake where the headers are.

## Running

### Running without order

Assuming that you have already built **dose_to_plink** and added it to your path. You can run the following command to transpose the given chunk.prob.gz, and store it into transposed.prob.gz

    dose_to_plink -t prob -i chunk.info.gz -d chunk.prob.gz -o transposed.prob.gz

### Running with order

When you want the individuals in a specific order, you need to create a separate file that tells **dose_to_plink** which order. This is the example order.txt:

    iid1
    iid4
    iid3
    iid2

Now you can run **dose_to_plink** as follows:

    dose_to_plink -t prob -i chunk.info.gz -d chunk.prob.gz --order-file order.txt -o transposed.prob.gz

### Running with aliases

Sometimes it can be convenient to change the names of the individuals. In this case we create a file called alias.txt that maps old iids and fids to new ones:

    old_fid1 old_iid1 new_fid1 new_iid1
    old_fid2 old_iid2 new_fid2 new_iid2
    old_fid3 old_iid3 new_fid3 new_iid3
    old_fid4 old_iid4 new_fid4 new_iid4

Now you can run **dose_to_plink** as follows:

    dose_to_plink -t prob -i chunk.info.gz -d chunk.prob.gz --alias-file alias.txt -o transposed.prob.gz
