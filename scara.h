#ifndef SCARA_H
#define SCARA_H

#include <string>

class Scara {
public:

  Scara();
  static void starte(std::string level);
  static void starte(std::string level, int szenario);
  static void beende();

  static void gehe();
  static void dreheLinks();
  static bool istVorneAbgrund();
  static bool stehtAufAnkh();
  static bool istVornePalette();
  static int  holePalettenhoehe();
  static void nimmPalette();
  static void legePalette();
  static bool istVorneWand();
  static void zeigeDrehung(bool drehung);
  static void setzeTempo(int tempo);
  static void schiebeStein();
  static bool istSteinVerschiebbar();
  static bool istVornePlatzFuerStein();
  static bool istVornePlatzFuerPalette();
  static int  scanne();
  static void springe(int distanz);
  static void springeZu(int xPos, int yPos);
  static int  holeXPosition();
  static int  holeYPosition();
  static int  holeBlickrichtung();
  static bool stehtAufGlyphe();
  static int  holeGlyphenwert();
  static void speicherePosition();
  static void springeZurueck();
  static bool sindPositionenGespeichert();
  static bool stehtAufTerminal();
  static int  holeTerminalwert();
  static int  holeTerminalnummer();
  static void setzeTerminalwert(int wert);
  static void loeseLevel();
  static bool istVorneFalle();
  static int  holeLevelbreite();
  static int  holeLevelhoehe();
  static void setzeMarker();
  static void setzeMarkerVor(int distanz);
  static void setzeMarkerAuf(int xPos, int yPos);
  static void wandlePaar();
  static void entfernePaar();
  static void warte(int sekunden);
  static bool istVornePyramide();
  static int  holePyramidenwert();
  static int  scanneMarker();
  static int  scannePosition(int xPos, int yPos);

};

#endif // SCARA_H
