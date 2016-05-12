#ifndef vectorH
#define vectorH

class Vector{

    public:
        Vector();
        Vector(float a, float o);
        float getAbscisa() const;
        float getOrdenada() const;
        bool igualX(const Vector v);
        bool igualY(const Vector v);
        float modulo() const;
        float prodEscalar(const Vector v) const;
        void resta(const Vector v);

    private:
        float abscisa;
        float ordenada;
};

#endif

