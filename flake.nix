{
  description = "Suckless tools: dmenu-flexipatch, dwm, st-flexipatch";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachSystem [ "x86_64-linux" ] (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        
        # Common make flags to override hardcoded paths in config.mk
        sucklessMakeFlags = [
          "PREFIX=$(out)"
          "MANPREFIX=$(out)/share/man"
          "X11INC=" 
          "X11LIB=" 
          "FREETYPEINC=" 
        ];
      in
      {
        packages = {
          dmenu = pkgs.stdenv.mkDerivation {
            pname = "dmenu-flexipatch";
            version = "5.4";
            src = ./dmenu-flexipatch;
            buildInputs = with pkgs; [ xorg.libX11 xorg.libXinerama xorg.libXft zlib ];
            installFlags = sucklessMakeFlags;
          };

          dwm = pkgs.stdenv.mkDerivation {
            pname = "dwm";
            version = "6.6";
            src = ./dwm;
            buildInputs = with pkgs; [ xorg.libX11 xorg.libXinerama xorg.libXft ];
            installFlags = sucklessMakeFlags;
          };

          st = pkgs.stdenv.mkDerivation {
            pname = "st-flexipatch";
            version = "0.9.3";
            src = ./st-flexipatch;
            nativeBuildInputs = [ pkgs.pkg-config pkgs.ncurses ];
            buildInputs = with pkgs; [ 
              xorg.libX11 
              xorg.libXft 
              xorg.libXrender 
              imlib2 
            ];
            installFlags = sucklessMakeFlags;
            
            # Ensure tic writes to the correct location
            preInstall = ''
              export TERMINFO=$out/share/terminfo
              mkdir -p $TERMINFO
            '';
          };

          dwmblocks-async = pkgs.stdenv.mkDerivation {
            pname = "dwmblocks-async";
            version = "unstable";
            src = ./dwmblocks-async;
            nativeBuildInputs = [ pkgs.pkg-config ];
            buildInputs = with pkgs; [ xorg.libxcb xorg.xcbutil ];
            installFlags = [ "PREFIX=$(out)" ];
          };
        };

        packages.default = pkgs.symlinkJoin {
          name = "suckless-suite";
          paths = [
            self.packages.${system}.dmenu
            self.packages.${system}.dwm
            self.packages.${system}.st
            self.packages.${system}.dwmblocks-async
          ];
        };
        
        devShells.default = pkgs.mkShell {
          inputsFrom = [ 
            self.packages.${system}.dmenu 
            self.packages.${system}.dwm 
            self.packages.${system}.st 
            self.packages.${system}.dwmblocks-async
          ];
          packages = [ pkgs.gnumake ];
        };
      }
    );
}