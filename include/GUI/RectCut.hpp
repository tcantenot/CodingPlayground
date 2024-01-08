#pragma once
#ifndef KIMERA_GUI_RECT_CUT_HPP
#define KIMERA_GUI_RECT_CUT_HPP


// TODO: AddX, Extend, Contract
// TODO: Add CutXPercent, GetXPercent

// Based on RectCut:
// http://web.archive.org/web/20230331132208/https://halt.software/dead-simple-layouts/
// https://github.com/nsmryan/rectcut-rs/blob/master/src/lib.rs

namespace KimeraUI {

struct Rect
{
	float minX;
	float minY;
	float maxX;
	float maxY;
};

// Min operator
template <typename T>
inline T RectCutMin(T const & lhs, T const & rhs)
{
	return lhs < rhs ? lhs : rhs;
}

// Max operator
template <typename T>
inline T RectCutMax(T const & lhs, T const & rhs)
{
	return lhs > rhs ? lhs : rhs;
}

// Cut out the left of the rect, returning the top piece and modifying the original rect.
inline Rect CutLeft(Rect * rect, float a)
{
	float minX = rect->minX;
	rect->minX = RectCutMin(rect->maxX, rect->minX + a);
	return { minX, rect->minY, rect->minX, rect->maxY };
}

// Cut out the right of the rect, returning the top piece and modifying the original rect.
inline Rect CutRight(Rect * rect, float a)
{
	float maxX = rect->maxX;
	rect->maxX = RectCutMax(rect->minX, rect->maxX - a);
	return { rect->maxX, rect->minY, maxX, rect->maxY };
}

// Cut out the top of the rect, returning the top part and modifying the original rect.
inline Rect CutTop(Rect * rect, float a)
{
	float minY = rect->minY;
	rect->minY = RectCutMin(rect->maxY, rect->minY + a);
	return { rect->minX, minY, rect->maxX, rect->minY };
}

// Cut out the bottom of the rect, returning the top piece and modifying the original rect.
inline Rect CutBottom(Rect * rect, float a)
{
	float maxY = rect->maxY;
	rect->maxY = RectCutMax(rect->minY, rect->maxY - a);
	return { rect->minX, rect->maxY, rect->maxX, maxY };
}

// Cut out the left of the rect, returning the top piece and leaving the original rect unmodified.
inline Rect GetLeft(Rect const & rect, float a)
{
	const float maxX = RectCutMin(rect.maxX, rect.minX + a);
	return { rect.minX, rect.minY, maxX, rect.maxY };
}

// Cut out the right of the rect, returning the top piece and leaving the original rect unmodified.
inline Rect GetRight(Rect const & rect, float a)
{
	const float minX = RectCutMax(rect.minX, rect.maxX - a);
	return { minX, rect.minY, rect.maxX, rect.maxY };
}

// Cut out the top of the rect, returning the top piece and leaving the original rect unmodified.
inline Rect GetTop(Rect const & rect, float a)
{
	const float maxY = RectCutMin(rect.maxY, rect.minY + a);
	return { rect.minX, rect.minY, rect.maxX, maxY };
}

// Cut out the bottom of the rect, returning the top piece and leaving the original rect unmodified.
inline Rect GetBottom(Rect const & rect, float a)
{
	const float minY = RectCutMax(rect.minY, rect.maxY - a);
	return { rect.minX, minY, rect.maxX, rect.maxY };
}

// Create a rect that extend the given rect out to the left, leaving the original rect unmodified.
inline Rect AddLeft(Rect const & rect, float a)
{
	return { rect.minX - a, rect.minY, rect.maxX, rect.maxY };
}

// Create a rect that extend the given rect out to the right, leaving the original rect unmodified.
inline Rect AddRight(Rect const & rect, float a)
{
	return { rect.minX, rect.minY, rect.maxX + a, rect.maxY };
}

// Create a rect that extend the given rect out to the top, leaving the original rect unmodified.
inline Rect AddTop(Rect const & rect, float a)
{
	return { rect.minX, rect.minY - a, rect.maxX, rect.maxY };
}

// Create a rect that extend the given rect out to the bottom, leaving the original rect unmodified.
inline Rect AddBottom(Rect const & rect, float a)
{
	return { rect.minX, rect.minY, rect.maxX, rect.maxY + a };
}

// Extend the given rect out in all directions, leaving the original rect unmodified.
inline Rect Extend(Rect const & rect, float a)
{
	return { rect.minX - a, rect.minY - a, rect.maxX + a, rect.maxY + a };
}

// Contract the given rect in all directions, leaving the original rect unmodified.
inline Rect Contract(Rect const & rect, float a)
{
	const float maxX = rect.maxX - a;
	const float maxY = rect.maxY - a;
	const float minX = RectCutMax(maxX, rect.minX + a);
	const float minY = RectCutMax(maxY, rect.minY + a);
	return { minX, minY, maxX, maxY };
}

}

#endif //KIMERA_GUI_RECT_CUT_HPP
