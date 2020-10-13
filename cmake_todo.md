# CMake TODO

1. Add Altair license to all the new files
2. Utilize the transitivity of cmake object properties (include directories, link libraries etc.), properly mark them PRIVATE, PUBLIC or INTERFACE
   Right now all properties are marked PRIVATE. THe side effect of this is that all targets have to explicity list all include dirs and all libraries they links to. 
3. Fill in the missing configration options and build time dependencies. For example, KRB5_args KRB5_flags, what are these?
4. These cmake changes were made and tested on centos 7. Need to test on platforms other than centos 7.
5. Add cmake files for installing ptl
6. I was able to create a single openpbs package using cpack. Need to create the client, execution, debuginfo and devel package
7. I run ldconfig in the postinstall script, is there a better way 
8. As a last step, remove all autotool files.