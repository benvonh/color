{
  description = "Generate an accent or font color from an image";

  inputs.nixpkgs.url = "github:nixos/nixpkgs";

  outputs = { self, nixpkgs }: let

    pkgsFor = nixpkgs.legacyPackages;

    systems = nixpkgs.lib.platforms.all;

    forAllSystems = nixpkgs.lib.genAttrs systems;

  in
  {
    defaultPackage = forAllSystems (system: let
      pkgs = import nixpkgs { inherit system; };
    in
      pkgs.stdenv.mkDerivation {
        name = "color";
        src = self;
        buildPhase = "${pkgsFor.${system}.gcc}/bin/gcc -o color -lm main.c";
        installPhase = "install -D -t $out/bin color";
      }
    );
  };
}
