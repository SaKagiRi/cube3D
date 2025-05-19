{
  description = "Cube3D flake for exact dependency lock";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
    utils.url = "github:numtide/flake-utils";
    flake-compat.url = "https://flakehub.com/f/edolstra/flake-compat/1.tar.gz";
  };

  outputs = { self, nixpkgs, utils, flake-compat }: utils.lib.eachDefaultSystem (system:
  let
    pkgs = import nixpkgs {
      inherit system;
      config = {
        allowUnfree = true;
      };
      
    };
    stdenv = pkgs.clangStdenv;
  in
  {
	
    devShells.default = stdenv.mkDerivation {
      name = "Cube3D-nix";
      src = ./srcs;
      buildInputs = with pkgs; [
        mesa
        clang
        clang-tools
        pkg-config
        xorg.libX11
        libGL
        glxinfo
        freeglut  # For example, use FreeGLUT if you're using it
        cmake     # If you need to use CMake
        glfw
      ];
      shellHook = ''
        export LD_LIBRARY_PATH="${stdenv.cc.cc.lib}/lib/":$LD_LIBRARY_PATH
        export LD_LIBRARY_PATH="${pkgs.glib.out}/lib":$LD_LIBRARY_PATH
        export LD_LIBRARY_PATH="${pkgs.lib.makeLibraryPath [pkgs.libGL]}":$LD_LIBRARY_PATH
        export LD_LIBRARY_PATH=/run/opengl-driver/lib/:$LD_LIBRARY_PATH
        # source $src/.nixshell_rc
      '';
    };
  });
} 

