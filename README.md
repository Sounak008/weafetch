# weafetch
Small weather fetch tool made using C.
It uses the free API from [weatherapi.com](https://weatherapi.com).

<img width="629" height="309" alt="image" src="https://github.com/user-attachments/assets/4306addb-b883-44e6-8046-90f5a6346dbc" />


Has been only tested in Fedora Linux as of now.

---
## Dependencies
### Linux
- libcurl4-openssl-dev (apt) or libcurl-devel (rpm)
### Windows
- mingw-w64-x86_64-curl (MSYS2)
### MacOS
- curl (brew)

---

## Usage

1. Grab the binary from [github releases](https://github.com/Sounak008/weafetch/releases).
2. Run 

  ```bash
  ./path/to/file -t City_Name
  ```



# Build Instructions (Linux)

0. Install the dependencies as well as [gcc](https://www.google.com/search?q=gcc+installation+guide).

1. Clone the repo and cd into it:

  ```bash
  git clone git@github.com:Sounak008/weafetch.git
  ```

  ```bash
  cd weafetch
  ```

2. Run the following commands:

```bash
gcc main.c api.c cJSON.c -o weafetch -lcurl
```

```bash
./weafetch
```
