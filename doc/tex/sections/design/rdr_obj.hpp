class rdr_obj : public scenario {
public:
  // Render-Specific Functions Here
  void drawBody(int bodyID);
  void drawScene(void);
  // Check Coordinates - Return Body ID if any under cursor.
  int checkCoord(double x, double y);
};
