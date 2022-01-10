# Mario Paint
Example usage of splat for a n64dd game. Made at the request of @CrookedPoe.

## Building (Linux)

### Install build dependencies
The build process has the following package requirements:
- git
- build-essential
- binutils-mips-linux-gnu
- python3

Under a Debian based distribution, you can install these with the following commands:
```
sudo apt update
sudo apt install git build-essential binutils-mips-linux-gnu python3
```

### Clone the repository
Clone `https://github.com/Drahsid/mario-paint.git` in whatever directory you wish. Make sure to initialize the submodules!
```
git clone https://github.com/Drahsid/mario-paint.git --recursive
cd mario-paint
git submodule init
```

### Install Python3 requirements
Navigate to `tools/splat/` and run `pip3 install -r requirements.txt`

### Prepare the base rom
Copy your n64dd file into the root of the repository with the name `mario-paint.ndd`. Following this, run `make extract_rom`. After this, you can run `make setup` to extract the assets of the rom.

### Build the rom
Just run `make` to build the rom. If the build succeeds, a folder will be produced with the name `build`, inside this will be the output rom `mario-paint.z64dd`.

