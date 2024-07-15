#ifndef MATRIX_H
#define MATRIX_H

#include <QPoint>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
class Matrix
{
private:
    unsigned sz1, sz2, ll, lc;
    vector<vector<T>> elems;
public:
    Matrix(unsigned sz1, unsigned sz2);
    Matrix();

    unsigned get_sz1() const;
    unsigned get_sz2() const;

    void add_line(vector<T> line, unsigned i);
    void add_colum(vector<T> line, unsigned j);
    void push_back_line(vector<T> line);
    void push_back_colum(vector<T> line);

    const vector<T>& operator[](unsigned i) const;
    vector<T>& operator[](unsigned i);

    template<class V>
    friend Matrix<V> operator+(const Matrix<V>& mat1, const Matrix<V>& mat2);
    template<class V>
    friend Matrix<V> operator-(const Matrix<V>& mat1, const Matrix<V>& mat2);
    template<class V>
    friend Matrix<V> operator*(const Matrix<V>& mat1, const Matrix<V>& mat2);
    template<class V>
    friend Matrix<V> operator*(const Matrix<V>& mat, const V& value);
    template<class V>
    friend Matrix<V> operator*(const V& value, const Matrix<V>& mat);

    void transpose();
  //  Matrix<T>& operator+=(const Matrix<T> mat);

  //  Matrix<T>& operator*=(const Matrix<T> mat);
  //  Matrix<T>& operator*=(const T& value);

 //   Matrix<T>& operator-=(const Matrix<T> mat);


    static QPointF matToPointF(Matrix<T>& m, QPointF* p = NULL);
    static QPoint matToPoint(Matrix<T>& m, QPoint* p = NULL);

    static void pointToMatF(QPointF p, Matrix<T>& m);

    static void pointToMat(QPoint p, Matrix<T>& m);


    static Matrix<T> rotateMat(double rad);
    static Matrix<T> transferMat(double x, double y);
    static Matrix<T> scalingMat(double kx, double ky);
    Matrix<T> reflectionXMat();
    Matrix<T> reflectionYMat();

    //static Matrix<T>* reflectionMat();

    static QPoint getChangedPoint(QPoint sourceP, Matrix<T>* changeMat);
    static QPointF getChangedPointF(QPointF sourceP, Matrix<T>* changeMat);

    static QPointF getRotatedPoint(QPointF sourceP, qreal rad, QPointF O = QPointF(0, 0));
    static QPointF getScaledPoint(QPointF sourceP, double kx, double ky);
};


template<class T>
Matrix<T>::Matrix(unsigned sz1, unsigned sz2) :sz2(sz2), sz1(sz1)
{
    elems.resize(sz1);
    for (auto &i : elems)
        i.resize(sz2);
    ll = lc = 0;
}

template<class T>
Matrix<T>::Matrix()
{
    unsigned sz = 3;
    elems.resize(sz);
    for (auto &i : elems)
        i.resize(sz);
    ll = lc = 0;
}


template<class T>
unsigned Matrix<T>::get_sz1() const
{
    return sz1;
}

template<class T>
unsigned Matrix<T>::get_sz2() const
{
    return sz2;
}


template<class T>
void Matrix<T>::add_line(vector<T> line, unsigned i)
{
    if (line.size() != sz2)
        throw "Wrong sizes";
    elems[i] = line;
}

template<class T>
void Matrix<T>::add_colum(vector<T> line, unsigned j)
{
    if (line.size() != sz1)
        throw "Wrong sizes";
    for (unsigned i = 0; i < sz1; i++)
        elems[i][j] = line[i];
}

template<class T>
void Matrix<T>::push_back_line(vector<T> line)
{
    elems[ll++] = line;
}

template<class T>
void Matrix<T>::push_back_colum(vector<T> line)
{
    this->add_colum(line, lc);
    lc++;
}


template<class T>
Matrix<T> Matrix<T>::rotateMat(double rad)
{
    Matrix<T> res(3, 3);
    res.push_back_line({cos(rad), -sin(rad), 0});
    res.push_back_line({sin(rad), cos(rad), 0});
    res.push_back_line({0, 0, 1});
    return res;
}

template<class T>
Matrix<T> Matrix<T>::transferMat(double x, double y)
{
    Matrix<T> res(3, 3);
    res.push_back_line({1, 0, x});
    res.push_back_line({0, 1, y});
    res.push_back_line({0, 0, 1});
    return res;
}

template<class T>
Matrix<T> Matrix<T>::scalingMat(double kx, double ky)
{
    Matrix<T> res(3, 3);
    res.push_back_line({kx, 0, 0});
    res.push_back_line({0, ky, 0});
    res.push_back_line({0, 0, 1});
    return res;
}

template<class T>
Matrix<T> Matrix<T>::reflectionXMat()
{
    Matrix<T> res(3, 3);
    res->push_back_line({-1, 0, 0});
    res->push_back_line({0, 1, 0});
    res->push_back_line({0, 0, 1});
    return res;
}

template<class T>
Matrix<T> Matrix<T>::reflectionYMat()
{
    Matrix<T> res(3, 3);
    res->push_back_line({1, 0, 0});
    res->push_back_line({0, -1, 0});
    res->push_back_line({0, 0, 1});
    return res;
}



template<class T>
const vector<T>& Matrix<T>::operator[](unsigned i) const
{return elems[i];}

template<class T>
vector<T>& Matrix<T>::operator[](unsigned i)
{return elems[i];}



template<class V>
Matrix<V> operator+(const Matrix<V>& mat1, const Matrix<V>& mat2)
{
    unsigned n1, n2; n1 = mat1.get_sz2(); n2 = mat2.get_sz2();
    unsigned m1, m2; m1 = mat1.get_sz1(); m2 = mat2.get_sz1();


    if (n1 != n2 || m1 != m2)
        throw "Wrong sizes";
    else
    {
        Matrix<V> res(m1, n1);
        for (unsigned i = 0; i < m1; i++)
            for (unsigned j = 0; j < n1; j++)
                res[i][j] = mat1[i][j] + mat2[i][j];
        return res;
    }
}

template<class V>
Matrix<V> operator-(const Matrix<V>& mat1, const Matrix<V>& mat2)
{
    unsigned n1, n2; n1 = mat1.get_sz2(); n2 = mat2.get_sz2();
    unsigned m1, m2; m1 = mat1.get_sz1(); m2 = mat2.get_sz1();


    if (n1 != n2 || m1 != m2)
        throw "Wrong sizes";
    else
    {
        Matrix<V> res(m1, n1);
        for (unsigned i = 0; i < m1; i++)
            for (unsigned j = 0; j < n1; j++)
                res[i][j] = mat1[i][j] - mat2[i][j];
        return res;
    }
}

template<class V>
Matrix<V> operator*(const Matrix<V>& mat1, const Matrix<V>& mat2)
{
    unsigned n1, n2; n1 = mat1.get_sz2(); n2 = mat2.get_sz2();
    unsigned m1, m2; m1 = mat1.get_sz1(); m2 = mat2.get_sz1();


    if (n1 != m2)
        throw "Wrong sizes";
    else
    {
        Matrix<V> res(m1, n2);
        for (unsigned i = 0; i < m1; i++)
            for (unsigned j = 0; j < n2; j++)
            {
                res[i][j] = 0;
                for (unsigned k = 0; k < m2; k++)
                    res[i][j] += mat1[i][k] * mat2[k][j];
            }
        return res;
    }
}

template<class V>
Matrix<V> operator*(const Matrix<V>& mat, const V& value)
{
    unsigned m, n;
    m = mat.get_sz1();
    n = mat.get_sz2();
    Matrix<V> res(m, n);
    for (unsigned i = 0; i < m; i++)
        for (unsigned j = 0; j < n; j++)
            res[i][j] = value * mat[i][j];
    return res;
}

template<class V>
Matrix<V> operator*(const V& value, const Matrix<V>& mat)
{return mat * value;}

/*template<class V>
Matrix<V>& Matrix<V>::operator+=(const Matrix<V> mat)
{
    unsigned m, n;
    m = mat.get_m();
    n = mat.get_sz2();
    if (n != this->get_sz2() || m != this->get_m())
        throw "Wrong sizes";
    else
    {
        for (unsigned i = 0; i < m; i++)
            for (unsigned j = 0; j < n; j++)
                elems[i][j] += mat[i][j];
        return (*this);
    }
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T> mat)
{
    unsigned n;
    unsigned m;

    n = mat.get_n();
    m = mat.get_m();
    if (this->m != m)
        throw "Wrong sizes";
    else
    {
        vector<T> buff(n);
        for (unsigned i = 0; i < this->m; i++)
        {
            for (unsigned j = 0; j < n; j++)
            {
                buff[j] = 0;
                for (unsigned k = 0; k < m; k++)
                    buff[j] += elems[i][k] * mat[k][j];
            }
            this->add_line(buff, i);
        }
        return (*this);
    }
} */

/*template<class T>
Matrix<T>& Matrix<T>::operator*=(const T& value)
{
    for (unsigned i = 0; i < m; i++)
        for (unsigned j = 0; j < n; j++)
            elems[i][j] *= value;
} */

/*template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T> mat)
{
    unsigned m, n;
    m = mat.get_m();
    n = mat.get_n();
    if (n != this->get_n() || m != this->get_m())
        throw "Wrong sizes";
    else
    {
        for (unsigned i = 0; i < m; i++)
            for (unsigned j = 0; j < n; j++)
                elems[i][j] -= mat[i][j];
        return (*this);
    }
} */

template<class T>
void Matrix<T>::transpose()
{
    for (unsigned i = 0; i < sz1; i++)
        for (unsigned j = i + 1; j < sz2; j++)
            swap(elems[i][j], elems[j][i]);
}




template<class T>
void Matrix<T>::pointToMatF(QPointF p, Matrix<T>& m)
{
    m[0][0] = p.x();
    m[1][0] = p.y();
    m[2][0] = 1;
}

template<class T>
void Matrix<T>::pointToMat(QPoint p, Matrix<T>& m)
{
    m[0][0] = p.x();
    m[1][0] = p.y();
    m[2][0] = 1;
}

template<class T>
QPointF Matrix<T>::matToPointF(Matrix<T>& m, QPointF* p)
{
    QPointF fp(m[0][0], m[1][0]);
    if (p != NULL)
        *p = fp;
    return fp;
}

template<class T>
QPoint Matrix<T>::matToPoint(Matrix<T>& m, QPoint* p)
{
    QPoint fp(m[0][0], m[1][0]);
    if (p != NULL)
        *p = fp;
    return fp;
}

template<class T>
QPointF Matrix<T>::getRotatedPoint(QPointF sourceP, qreal rad, QPointF O)
{
    Matrix<T> p(3, 1);
    pointToMat(sourceP, p);

    Matrix<T> M = Matrix<T>::transferMat(-O.x(), -O.y()) *
                  Matrix<T>::rotateMat(rad) *
                  Matrix<T>::transferMat(O.x(), O.y());

    Matrix<T> res(3, 1);
    res = M * p;

    return matToPoint(res);
}

template<class T>
QPointF Matrix<T>::getScaledPoint(QPointF sourceP, double kx, double ky)
{
    Matrix<T> p(3, 1);
    pointToMat(sourceP, p);


    return matToPoint(Matrix<T>::scalingMat(kx, ky) * p);
}

template<class T>
QPointF Matrix<T>::getChangedPointF(QPointF sourceP, Matrix<T>* changeMat)
{
    Matrix<T> p(3, 1);
    pointToMatF(sourceP, p);

    Matrix<T> res(3, 1);
    res = (*changeMat) * p;
    return matToPointF(res);
}

template<class T>
QPoint Matrix<T>::getChangedPoint(QPoint sourceP, Matrix<T>* changeMat)
{
    Matrix<T> p(3, 1);
    pointToMat(sourceP, p);

    Matrix<T> res(3, 1);
    res = (*changeMat) * p;
    return matToPoint(res);
}
#endif // MATRIX_H
