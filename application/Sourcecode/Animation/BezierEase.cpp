#include "BezierEase.h"
#include "Lerp.h"
#include "Vector2.h"
#include "Vector3.h"
#include <cassert>

using YMath::BezierEase;

template<typename T>
void BezierEase<T>::Initialize(const std::vector<T>& points, const float exponent)
{
	// 1‚Â‚à‚È‚¢‚È‚ç’e‚­
	assert(points.empty() == false);

	// ‘ã“ü
	points_ = points;
	exponent_ = exponent;
}

template<typename T>
T BezierEase<T>::In(const float ratio) const { return BezierEaseIn<T>(points_, ratio, exponent_); }

template<typename T>
T BezierEase<T>::Out(const float ratio) const { return BezierEaseOut<T>(points_, ratio, exponent_); }

template<typename T>
T BezierEase<T>::InOut(const float ratio, const float controlPoint) const { return BezierEaseInOut<T>(points_, ratio, exponent_, controlPoint); }

template<typename T>
T BezierEase<T>::OutIn(const float ratio, const float controlPoint) const { return BezierEaseOutIn<T>(points_, ratio, exponent_, controlPoint); }

template class BezierEase<float>;
template class BezierEase<double>;
template class BezierEase<Vector2>;
template class BezierEase<Vector3>;