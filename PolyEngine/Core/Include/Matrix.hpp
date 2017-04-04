#pragma once

#include <pmmintrin.h>

#include "Defines.hpp"
#include "BasicMath.hpp"
#include "Vector.hpp"
#include "Angle.hpp"

namespace Poly {

	class ALIGN_16 DLLEXPORT Matrix : public BaseObject<>{
	public:
	  Matrix();
	  Matrix(const float data[16], bool rowOrder = true);

	  Matrix(const Matrix& rhs);
	  Matrix& operator=(const Matrix& rhs);

	  bool operator==(const Matrix& rhs) const;
	  inline bool operator!=(const Matrix& rhs) const { return !(*this == rhs); }

	  Matrix operator*(const Matrix& rhs) const;
	  Matrix& operator*=(const Matrix& rhs);

	  Vector operator*(const Vector& rhs) const;

	  /**
	   *  Calculates the determinant of the matrix.
	   *
	   *  @return Determinant of the matrix.
	   */
	  float Det() const;

	  /**
	   *  Initializes matrix as identity matrix.
	   *
	   *  @return Reference to itself.
	   */
	  Matrix& SetIdentity();

	  /**
	   *  Initializes matrix with rotation about X axis.
	   *
	   *  @param[in] angle Angle in degrees.
	   *  @return Reference to itself.
	   */
	  Matrix& SetRotationX(Angle angle);

	  /**
	   *  Initializes matrix with rotation about Y axis.
	   *
	   *  @param[in] angle Angle in degrees.
	   *  @return Reference to itself.
	   */
	  Matrix& SetRotationY(Angle angle);

	  /**
	   *  Initializes matrix with rotation about Z axis.
	   *
	   *  @param[in] angle Angle in degrees.
	   *  @return Reference to itself.
	   */
	  Matrix& SetRotationZ(Angle angle);

	  /**
	   *  Initializes matrix with translation by the desired vector.
	   *
	   *  @param[in] direction Vector describing the translation.
	   *  @return Reference to itself.
	   */
	  Matrix& SetTranslation(const Vector& direction);

	  /**
	   *  Initializes matrix with proportional scaling.
	   *
	   *  @param[in] scale Scale for all three dimensions.
	   *  @return Reference to itself.
	   */
	  Matrix& SetScale(float scale);

	  /**
	   *  Initializes matrix with scaling.
	   *
	   *  @param[in] scale Scale vector for each of the three dimensions.
	   *  @return Reference to itself.
	   */
	  Matrix& SetScale(const Vector& scale);

	  /**
	   *  Inverses the matrix.
	   *
	   *  @return Reference to itself after the inversion.
	   */
	  Matrix& Inverse();

	  /**
	   *  Creates inversed matrix from this one.
	   *
	   *  @return New, inversed matrix object.
	   */
	  Matrix GetInversed() const;

	  /**
	   *  Transposes the matrix.
	   *
	   *  @return Reference to itself after the transposition.
	   */
	  Matrix& Transpose();

	  /**
	   *  Creates transposed matrix from this one.
	   *
	   *  @return New, transposed matrix object.
	   */
	  Matrix GetTransposed() const;

	  DLLEXPORT friend std::ostream& operator<< (std::ostream& stream, const Matrix& mat);

	  // This structure allows to access vector elements by index or name.
	  union {
	#if !DISABLE_SIMD
		__m128 SimdRow[4];
	#endif
		float Data[16];
		struct {
		  float m00, m01, m02, m03;
		  float m10, m11, m12, m13;
		  float m20, m21, m22, m23;
		  float m30, m31, m32, m33;
		};
	  };
	};

}