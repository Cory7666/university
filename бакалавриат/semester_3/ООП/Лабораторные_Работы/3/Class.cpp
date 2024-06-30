#include "Class.hpp"

Aircraft::Aircraft () :
    Aircraft("Н/Д", 0, 0.0, 0.0)                     { }
Aircraft::Aircraft (const long s, const double fl, const double fc) :
    Aircraft("Н/Д", s, fl, fc)                       { }
Aircraft::Aircraft (const string t, const long s, const double fl, const double fc) :
    type(t), fuel_cons(fc), fuel_level(fl), speed(s) { }

string Aircraft::getType  ()        { return type;  }
const long   Aircraft::getSpeed ()        { return speed; }
const double Aircraft::getFLevel()        { return fuel_level; }
const double Aircraft::getFConsumption () { return fuel_cons;  }

Aircraft & Aircraft::setType  (string t) { type = t; return *this;  }
Aircraft & Aircraft::setSpeed (long s)   { speed = s; return *this; }
Aircraft & Aircraft::setFLevel(double fl)        { fuel_level = fl; return *this; }
Aircraft & Aircraft::setFConsumption (double fc) { fuel_cons = fc; return *this;  }

const double Aircraft::getEstimatedRange () { return ( (fuel_level / fuel_cons) * ( (double) speed ) ); }



