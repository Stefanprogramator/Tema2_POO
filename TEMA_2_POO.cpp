#include<iostream>
using namespace std;

class Complex   // Clasa de numere complexe
{
    float re,im;    // Partea reala + Partea imaginara
public:
    Complex()   //Constructor neparametrizat
    {
        re=0;
        im=0;
    }
    Complex(float real , float imag)    // Constructor parametrizat
    {
        re=real;
        im=imag;
    }
    Complex(const Complex& c)   // Constructor de copiere
    {
        re=c.re;
        im=c.im;
    }

    friend istream& operator>>(istream& , Complex &);
    friend ostream& operator<<(ostream& , Complex );
    friend bool operator==(Complex , Complex);
    friend bool operator!=(Complex , Complex);

    Complex get(){Complex c(re,im); return c;}
    void set(Complex c){re=c.re;im=c.im;}
    int getRe(){return re;}
    void setRe(int x){re=x;}
    int getIm(){return im;}
    void setIm(int x){im=x;}

    friend Complex operator+(Complex , Complex);
    friend Complex operator*(Complex , Complex);
    Complex operator=(Complex );

    friend class Matrice;
};


class Matrice   // Clasa matrice abstracta
{
protected:
    Complex **v;  // Matrice de numere complexe
public:

    Matrice()   // Constructor neparametrizat
{
    v=NULL;
}

    Matrice(int lin , int col)  // Constructor parametrizat
{
    v=new Complex*[lin];
    for(int i=0;i<lin;i++)
        {
            v[i]=new Complex[col];
            for(int j=0;j<col;j++)
                cin>>this->v[i][j];
        }
}


    // Metode virtuale pure
    virtual istream& citire(istream&)=0;
    virtual ostream& afisare(ostream&) const=0;

};


class Matrice_oarecare: public Matrice  // Mostenire clasa Matrice
{
protected:
    int lin,col;

public:

    Matrice_oarecare():Matrice()
{
        lin=0;
        col=0;
}

    Matrice_oarecare(const Matrice_oarecare &M)
{
    lin=M.lin;
    col=M.col;
    v=new Complex*[lin];
    for(int i=0;i<lin;i++)
        {
            v[i]=new Complex[col];
            for(int j=0;j<col;j++)
                v[i][j]=M.v[i][j];
        }
}

    ~Matrice_oarecare()
{
    for(int i=0;i<lin;i++)
        delete[] v[i];
    delete [] v;
}


    istream& citire(istream&);
    ostream& afisare(ostream&) const;

    friend istream& operator>>(istream& , Matrice_oarecare&);
    friend ostream& operator<<(ostream& , const Matrice_oarecare);

    Matrice_oarecare operator=(const Matrice_oarecare);

    bool Matrice_triunghiulara_sup();
    bool Matrice_triunghiulara_inf();
    void Matrice_diagonala();

};


class Matrice_patratica: public Matrice //  Mostenire clasa Matrice
{
protected:
    int dim;
public:
    Matrice_patratica():Matrice()
    {
        dim=0;
    }

    Matrice_patratica(int d ):Matrice(d,d)
    {
        cout<<"Clasa baza"<<endl;
    }

    Matrice_patratica(const Matrice_patratica& M)
    {
    dim=M.dim;
    v=new Complex*[dim];
    for(int i=0;i<dim;i++)
        {
            v[i]=new Complex[dim];
            for(int j=0;j<dim;j++)
                v[i][j]=M.v[i][j];
        }
    }

    ~Matrice_patratica()
    {
    for(int i=0;i<dim;i++)
        delete[] v[i];
    delete [] v;
    }

    int getDim()
    {
        return dim;
    }

    istream& citire(istream&);
    ostream& afisare(ostream&) const;

    friend istream& operator>>(istream& , Matrice_patratica&);
    friend ostream& operator<<(ostream& , const Matrice_patratica);

    Matrice_patratica operator=(const Matrice_patratica);

    Complex determinant()const;

    bool Matrice_triunghiulara_sup();
    bool Matrice_triunghiulara_inf();
    void Matrice_diagonala();

};



//  Metode clasa Complex

istream& operator>>(istream& in, Complex &c)
{
    in>>c.re>>c.im;
    return in;
}
ostream& operator<<(ostream& out, Complex  c)
{
    out<<c.re<<" + "<<c.im<<"i ";
    return out;
}

Complex Complex::operator=(Complex c)
{
    re=c.re;
    im=c.im;
    return c;
}

Complex operator+(Complex c1, Complex c2)
{
    Complex c;
    c.re=c1.re+c2.re;
    c.im=c1.im+c2.im;
    return c;
}

Complex operator*(Complex c1, Complex c2)
{
    Complex c;
    c.re=c1.re*c2.re-c1.im*c2.im;
    c.im=c1.re*c2.im+c1.im*c2.re;
    return c;
}

bool operator==(Complex c1, Complex c2)
{
    if(c1.re == c2.re && c1.im==c2.im)
        return 1;
    return 0;
}

bool operator!=(Complex c1, Complex c2)
{
    if(c1.re != c2.re || c1.im!=c2.im)
        return 1;
    return 0;
}

//----------------------------------------------------

// Metode matrice_oarecare

istream& Matrice_oarecare::citire(istream& in)
{
    if(v != NULL)
        {
            for(int i=0;i<lin;i++)
                delete[] v[i];
            delete [] v;
        }
    cout<<"Numarul de linii este: "<<endl;
    in>>lin;
    cout<<"Numarul de coloane este: "<<endl;
    in>>col;

    cout<<endl<<"Numerele complexe din matrice sunt: "<<endl;

    v=new Complex*[lin];
    for(int i=0;i<lin;i++)
        v[i]=new Complex[col];

    for(int i=0;i<lin;i++)
        for(int j=0;j<col;j++)
        in>>v[i][j];
    return in;
}

ostream& Matrice_oarecare::afisare(ostream& out) const
{
    if(lin == 0)
        {
            out<<"Matrice nula"<<endl;
            return out;
        }
    for(int i=0;i<lin;i++)
    {
        for(int j=0;j<col;j++)
            out<<v[i][j]<<' ';
        out<<endl;
    }
    return out;
}

Matrice_oarecare Matrice_oarecare::operator=(const Matrice_oarecare M)
{
        if(this != NULL)
        {
            for(int i=0;i<lin;i++)
                delete[] v[i];
            delete [] v;
        }
        lin=M.lin;
        col=M.col;
        v=new Complex*[lin];
        for(int i=0;i<lin;i++)
        {
            v[i]=new Complex[col];
        }
        for(int i=0;i<lin;i++)
            for(int j=0;j<col;j++)
            v[i][j]=M.v[i][j];
    return M;
}

istream& operator>>(istream& in, Matrice_oarecare& M)
{
    return M.citire(in);
}
ostream& operator<<(ostream& out, const Matrice_oarecare M)
{
    return M.afisare(out);
}

bool Matrice_oarecare::Matrice_triunghiulara_sup()
    {
        if(lin != col)
        {
        cout<<"Matricea introdusa nu este patratica"<<endl;
        return false;
        }

        Complex origine(0,0);

        for(int i=0;i<lin;i++)
            for(int j=i+1;j<col;j++)
            if(v[i][j] != origine)
            {
            return false;
            cout<<"Matricea nu este o matrice triunghiulara superior"<<endl;
            }

        return true;

    }


bool Matrice_oarecare::Matrice_triunghiulara_inf()
    {
        if(lin != col)
        {
        cout<<"Matricea introdusa nu este patratica"<<endl;
        return false;
        }

        Complex origine(0,0);

        for(int i=0;i<lin;i++)
            for(int j=0;j<i;j++)
            if(v[i][j] != origine)
            {
            return false;
            cout<<"Matricea nu este o matrice triunghiulara inferior"<<endl;
            }

        return true;

    }

void Matrice_oarecare::Matrice_diagonala()
    {
        if(Matrice_triunghiulara_inf() && Matrice_triunghiulara_sup())
            cout<<"Matricea introdusa este o matrice diagonala";
        else
            cout<<"Matricea introdusa NU este o matrice diagonala";
    }


//----------------------------------------------------------

// Metode clasa matrice_patratica

istream& Matrice_patratica::citire(istream& in)
{
    if(this->v != NULL)
        {
            for(int i=0;i<dim;i++)
                delete[] v[i];
            delete [] v;
        }
    cout<<"Dimensiune:"<<endl;
    in>>dim;
    cout<<endl<<"Introduceti de la tastatura numerele complexe din matrice ( partea reala , enter,partea imaginara)"<<endl;

    v=new Complex*[dim];
    for(int i=0;i<dim;i++)
        v[i]=new Complex[dim];

    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
        in>>v[i][j];
    return in;
}

ostream& Matrice_patratica::afisare(ostream& out) const
{
    if(dim == 0)
        {
            out<<"Matrice nula"<<endl;
            return out;
        }
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
            out<<v[i][j]<<' ';
        out<<endl;
    }
    out<<"Determinantul este egal cu: "<<determinant()<<endl;
    return out;
}

Matrice_patratica Matrice_patratica::operator=(const Matrice_patratica M)
{
        if(this != NULL)
        {
            for(int i=0;i<dim;i++)
                delete[] v[i];
            delete [] v;
        }
        dim=M.dim;
        v=new Complex*[dim];
        for(int i=0;i<dim;i++)
        {
            v[i]=new Complex[dim];
        }
        for(int i=0;i<dim;i++)
            for(int j=0;j<dim;j++)
            v[i][j]=M.v[i][j];
    return M;
}

istream& operator>>(istream& in, Matrice_patratica& M)
{
    return M.citire(in);
}
ostream& operator<<(ostream& out, const Matrice_patratica M)
{

    return M.afisare(out);
}

void Matrice_factor(Complex **mat, Complex **temp, int p, int q, int n)
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

Complex det(Complex **mat, int n)
{
    Complex D(0,0);

    if (n == 1)
        return mat[0][0];

    Complex **temp=new Complex*[n];
    for(int i=0;i<n;i++)
        temp[i]=new Complex[n];

    Complex sign(1,0);

    for (int f = 0; f < n; f++)
    {
        Matrice_factor(mat, temp, 0, f, n);
        D =D + sign * mat[0][f] * det(temp, n - 1);

        sign.setRe(-sign.getRe());
    }
    for(int i=0;i<n;i++)
        delete [] temp[i];
    delete [] temp;
    return D;
}

Complex Matrice_patratica::determinant()const
{
    Matrice_patratica Mp(*this);
    return det(Mp.v,Mp.dim);
}

 bool Matrice_patratica::Matrice_triunghiulara_sup()
    {
        Complex origine(0,0);

        for(int i=0;i<dim;i++)
            for(int j=i+1;j<dim;j++)
            if(v[i][j] != origine)
            {
                cout<<"Matricea nu este o matrice triunghiulara superior"<<endl;
                return false;
            }

        return true;

    }


bool Matrice_patratica::Matrice_triunghiulara_inf()
    {
        Complex origine(0,0);

        for(int i=0;i<dim;i++)
            for(int j=0;j<i;j++)
            if(v[i][j] != origine)
            {
                cout<<"Matricea nu este o matrice triunghiulara inferior"<<endl;
                return false;
            }

        return true;

    }

void Matrice_patratica::Matrice_diagonala()
    {
        if(Matrice_triunghiulara_inf() && Matrice_triunghiulara_sup())
            cout<<"Matricea introdusa este o matrice diagonala";
        else
            cout<<"Matricea introdusa NU este o matrice diagonala";
    }

//---------------------------------------------------------------------




int main()

{
    /*Complex x;
    x.setRe(5);
    x.setIm(3);
    cout<<x;
    Complex y;
    y.setRe(2);
    y.setIm(3);
    cout<<endl<<y<<endl;
    cout<<x+y<<" "<<endl<<x*y;
    Complex a;
    cout<<a;*/

    /*Matrice_oarecare m;
    cin>>m;
    cout<<m;
    m.Matrice_diagonala();*/

    /*Matrice_patratica m;
    cin>>m;
    cout<<m;
    m.Matrice_diagonala();*/

    return 0;





}







