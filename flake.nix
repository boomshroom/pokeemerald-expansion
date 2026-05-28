{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  outputs = { nixpkgs, self }:
    let pkgs = nixpkgs.legacyPackages.x86_64-linux; in {
    devShells.x86_64-linux.default = pkgs.mkShell {
      name = "pokeemerald-expansion";
      buildInputs = [ pkgs.libpng pkgs.pkg-config pkgs.pkgsCross.arm-embedded.stdenv.cc ];
    };
  };
}
