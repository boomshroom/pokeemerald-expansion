{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  outputs = { nixpkgs, self }:
    let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;
      lib = pkgs.lib;
      rom-test = pkgs.mgba.overrideAttrs (old: {
        cmakeFlags = (old.cmakeFlags or []) ++ (lib.singleton <| lib.strings.cmakeBool "BUILD_ROM_TEST" true);
      });
    in {
    devShells.x86_64-linux.default = pkgs.mkShell {
      name = "pokeemerald-expansion";
      buildInputs = [ pkgs.libpng pkgs.pkg-config pkgs.pkgsCross.arm-embedded.stdenv.cc ];
      ROMTEST = lib.getExe' rom-test "mgba-rom-test";
    };
  };
}
