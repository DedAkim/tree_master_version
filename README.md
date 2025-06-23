# Student Practice C++: Prefix tree

**Search value in a prefix tree by number**

Implements prefix search tree algorigthm, search values belonging to numeric range or numeric prefix.

## Tasks

* Implement RangeAdd method of Prefix<T> class
* Do not use any macros in source code, i.e replace ctoi and itoi by functions or lambdas, or delete 
them if not will be used in RangeAdd methods
* Replace shared_ptr used for Prefix<T>::hash_t on unique_ptr
* Run tests, run benchmarks on different container libraries. 

Unit tests and descriptions for the declarations of the Grouping class in the header file will help in the implementation.
See example how to write tests and benchmarks at [Sort Keys Example](git@github.com:AlexBurnes/practice-sort_keys.git)


## Author

Aleksey.Ozhigov <AlexBurnes@gmail.com>

## Version

0.1.0

## Change log

For detail history changes, see [CHANGELOG](CHANGELOG.md)

## Build

    git submodule init
    git submodule update
    docker build --tag practice_prefix_tree:latest --network host --progress=plain .

## Test Coverage

To view test coverage, run a Docker container:

    docker run -d --rm --name practice_prefix_tree --publish 8081:80 practice_prefix_tree

Then open your browser at [Coverage](http://localhost:8081)

## Code Style Check

For checking code style formatting the clang-format-19 utility is used.
The format is defined in style_format.txt, which is based on
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

    clang-format-19 --style="file:style_format.txt" source

# License

This work is distributed under the [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0), see
[LICENSE](https://github.com:AlexBurnes/practice-prefix_tree/blob/master/LICENSE) for more information.
