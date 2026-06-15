{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  outputs = { nixpkgs, self }:
    let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;
      lib = pkgs.lib;
      rom-test = pkgs.mgba.overrideAttrs (old: {
        cmakeFlags = (old.cmakeFlags or []) ++ (lib.singleton <| lib.strings.cmakeBool "BUILD_ROM_TEST" true);
      });
      superfamiconv = pkgs.stdenv.mkDerivation {
        pname = "superfamiconv";
        version = "0.11.0";
        src = pkgs.fetchFromGitHub {
          owner = "Optiroc";
          repo = "SuperFamiconv";
          tag = "v0.11.0";
          hash = "sha256-Cg6C8pxqYZOx3OYutcUhUOV1DCCDmze9t2/hL9iR47M=";
        };
        nativeBuildInputs = [ pkgs.cmake pkgs.installShellFiles ];
        installPhase = ''
          runHook preInstall
          installBin superfamiconv
          runHook postInstall
        '';
      };
      porymap = with pkgs.qt6; pkgs.stdenv.mkDerivation {
        pname = "porymap";
        version = "6.3.1";
        src = pkgs.fetchFromGitHub {
          owner = "huderlem";
          repo = "porymap";
          tag = "6.3.1";
          hash = "sha256-EG09aOgJrIe5X+e/SKcZn+mxkZ2N4mBmRxlEV3LYvgo=";
        };
        buildInputs = [ qtbase qtdeclarative ];
        nativeBuildInputs = [ wrapQtAppsHook pkgs.installShellFiles qmake ];
        installPhase = ''
          runHook preInstall
          installBin "porymap"
          runHook postInstall
        '';
      };
    in {
    devShells.x86_64-linux.default = pkgs.mkShell {
      name = "pokeemerald-expansion";
      buildInputs = [
        pkgs.libpng
        pkgs.pkg-config
        pkgs.pkgsCross.arm-embedded.stdenv.cc
        superfamiconv
        porymap
      ];
      ROMTEST = lib.getExe' rom-test "mgba-rom-test";
    };
  };
}
