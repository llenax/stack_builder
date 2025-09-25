{
  description = "c development flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-25.05";
    flake-utils.url = "github:numtide/flake-utils";
    devenv.url = "github:cachix/devenv";
  };

  outputs = { self, ... }@inputs:
    inputs.flake-utils.lib.eachDefaultSystem(system:
      let
        pkgs = import inputs.nixpkgs {
          inherit system;
        };
      in
      {
        packages.default = pkgs.stdenv.mkDerivation {
          name = "stack_builder";
          src = self;
          nativeBuildInputs = [
            pkgs.meson
            pkgs.ninja
            pkgs.clang_19
            pkgs.clang-tools_19
            pkgs.pkg-config
            pkgs.raylib
            pkgs.cmake
          ];
          buildInputs = [
            pkgs.libGL
          ];
          buildPhase = ''
            CC="clang" meson setup build ../ --wipe
            meson compile -C build
          '';
          installPhase = ''
            mkdir -p $out/bin
            install -m 755 build/main $out/bin/stack_builder
          '';
        };

        devShells.default = inputs.devenv.lib.mkShell {
          inherit inputs pkgs;

          modules = [
            {
              packages = [
                pkgs.git
                pkgs.meson
                pkgs.ninja
                pkgs.clang_19
                pkgs.clang-tools_19
                pkgs.libGL
                pkgs.raylib
                pkgs.cmake
              ];

              enterShell = ''
                export CC="clang";
                export CXX="clang++";
                export CFLAGS="$(cat ${pkgs.clang_19}/nix-support/cc-cflags) $CFLAGS";
                export CFLAGS="$(cat ${pkgs.clang_19}/nix-support/libc-cflags) $CFLAGS";
                export CXXFLAGS="$(cat ${pkgs.clang_19}/nix-support/libcxx-cxxflags) $CXXFLAGS";
              '';
            }
          ];
        };
      }
    );
}
