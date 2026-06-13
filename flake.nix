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
    in {
    devShells.x86_64-linux.default = pkgs.mkShell {
      name = "pokeemerald-expansion";
      buildInputs = [ pkgs.libpng pkgs.pkg-config pkgs.pkgsCross.arm-embedded.stdenv.cc superfamiconv ];
      ROMTEST = lib.getExe' rom-test "mgba-rom-test";
    };
  };
}
