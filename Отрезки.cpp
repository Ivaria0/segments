#include <iostream>
#include <math.h>

using namespace std;

class Vector3D
{
private:
	double X;
	double Y;
	double Z;

public:
	Vector3D(double x = 0, double y = 0, double z = 0) : X(x), Y(y), Z(z) {}

	Vector3D vec_mul(Vector3D b) {
		return Vector3D(Y*b.Z-Z*b.Y, Z*b.X-X*b.Z, X*b.Y-Y*b.Z);
	}

	double det(Vector3D b, Vector3D c) {
		return X*b.Y*c.Z + Y*b.Z*c.X + Z*b.X*c.Y - Z*b.Y*c.X - Y*b.X*c.Z - X*b.Z*c.Y;
	}

	Vector3D sum(Vector3D b) {
		return Vector3D(X+b.X, Y+b.Y, Z+b.Z);
	}

	Vector3D sub(Vector3D b) {
		return Vector3D(X - b.X, Y - b.Y, Z - b.Z);
	}

	double scal_mul(Vector3D b) {
		return X*b.X + Y*b.Y + Z*b.Z;
	}

	double len() {
		return sqrt((*this).scal_mul(*this));
	}

	Vector3D mul(double a) {
		return Vector3D(a*X, a*Y, a*Z);
	}

	void output(int check) {
		if (check == 0)
			cout << X << "; " << Y << "; " << Z << endl;
	}

	double x() {
		return X;
	}

	double y() {
		return Y;
	}

	double z() {
		return Z;
	}
};

class Segment3D: private Vector3D
{
private:
	Vector3D start;
	Vector3D end;
	
public:
	Segment3D(Vector3D Start, Vector3D End) : start(Start), end(End) {}
	Vector3D vec() {
		return end.sub(start);
	}

	double dist(Segment3D B) {
		Vector3D M1 = start;
		Vector3D l1 = (*this).vec();
		Vector3D M2 = B.start;
		Vector3D l2 = B.vec();
		double V = fabs(M2.sub(M1).det(l1, l2));
		return V / l1.vec_mul(l2).len();
	}

	Vector3D Intersect(Segment3D B, int &check) {
		check = 0;
		Vector3D l1 = end.sub(start);
		Vector3D l2 = B.end.sub(B.start);
		Vector3D starts = B.start.sub((*this).start);

		double s = -1;
		if (l1.len() == 0 || l2.len() == 0) {
			cout << "zero segment" << endl;
			check = 1;
		}

		if (l1.vec_mul(l2).len() == 0) {
			cout << "Parallel lines" << endl;
			check = 1;
		}

		else if ((*this).dist(B) != 0) {
			cout << "Skew lines" << endl;
			check = 1;
		}

		else if (l1.y()*l2.x() - l1.x()*l2.y() != 0) {
			s = (l1.x()*starts.y() - l1.y()*starts.x()) / (l1.y()*l2.x() - l1.x()*l2.y());
		}

		else if (l1.z()*l2.y() - l1.y()*l2.z() != 0) {
			s = (l1.y()*starts.z() - l1.z()*starts.y()) / (l1.z()*l2.y() - l1.y()*l2.z());
		}

		else if (l1.z()*l2.x() - l1.x()*l2.z() != 0) {
			s = (l1.x()*starts.z() - l1.z()*starts.x()) / (l1.z()*l2.x() - l1.x()*l2.z());
		}

		if (s >= 0 && s <= 1)
			return B.start.sum(l2.mul(s));

		else
			cout << "No intersection" << endl;
			check = 1;
	}
};

int main()
{
	double l, m, n;

	cout << "Coordinates of start of a" << endl;
	cin >> l >> m >> n;
	Vector3D a1(l, m, n);

	cout << "Coordinates of end of a" << endl;
	cin >> l >> m >> n;
	Vector3D a2(l, m, n);

	cout << "Coordinates of start of b" << endl;
	cin >> l >> m >> n;
	Vector3D b1(l, m, n);

	cout << "Coordinates of end of b" << endl;
	cin >> l >> m >> n;
	Vector3D b2(l, m, n);

	Segment3D a(a1, a2);
	Segment3D b(b1, b2);

	int check = 0;

	Vector3D C = a.Intersect(b, check);

	C.output(check);
}
