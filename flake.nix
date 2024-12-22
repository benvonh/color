{
  description = "Generate a set of colors from an image to help theme your desktop environment";

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
      pkgs.stdenv.mkDerivation rec {
        name = "color";
        src = self;
        buildPhase = "${pkgsFor.${system}.gcc}/bin/gcc -o ${name} -lm main.c";
        installPhase = "install -D -t $out/bin ${name}";
      }
    );
  };
}
