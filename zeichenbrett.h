#ifndef ZEICHENBRETT_H
#define ZEICHENBRETT_H

#include <string>

class Zeichenbrett {
public:
  static void oeffnen(int breite, int hoehe);
  static void schliessen();
  static int holeBreite();
  static int holeHoehe();
  static int holeRot();
  static int holeGruen();
  static int holeBlau();
  static void setzeRot(int rot);
  static void setzeGruen(int gruen);
  static void setzeBlau(int blau);
  static int holeAlpha(); 
  static void setzeAlpha(int alpha);
  static void setzeAntialias(bool aktiv);
  static void setzeAutoaktualisierung(bool aktiv);
  static void aktualisiere();
  static void setzeLiniendicke(int dicke);
  static void zeichneLinie(int xStart, int yStart, int xEnde, int yEnde);
  static void zeichneSolideEllipse(int xPos, int yPos, int breite, int hoehe);
  static void zeichneEllipse(int xPos, int yPos, int breite, int hoehe);
  static void zeichneSolidesDreieck(int x1, int y1, int x2, int y2, int x3, int y3);

  // Koordinaten sind obere linke Ecke
  static void schreibeText(int xPos, int yPos, std::string text);
  static void schreibeText(int xPos, int yPos, std::wstring text);
  static void setzeSchriftgroesse(int groesse);
  static void setzeFettschrift(bool fett);
  static void zeichnePunkt(int xPos, int yPos);

  static int holeLiniendicke();

  static void warteAufKlick();
  static void loescheKlick();
  static void warte(int millisekunden);

  static int holeKlickX();
  static int holeKlickY();
  static bool istLinksklick();
  static bool istRechtsklick();
  static bool istMittelklick();
  static void speicherePng(std::string name, int kompression);
  static void speichereJpg(std::string name, int qualitaet);
};

#endif // ZEICHENBRETT_H
