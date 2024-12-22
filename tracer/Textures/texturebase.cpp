#include "texturebase.hpp"
#include <cmath>

sempRT::TextureBase::TextureBase()
{
}

sempRT::TextureBase::~TextureBase()
{
}

qbVector<double> sempRT::TextureBase::GetColor(const qbVector<double> &point)
{
    // Assuming the texture color vector has 4 elements (e.g., RGBA)
	qbVector<double> outputColor {4};
	
	// Return the output.
	return outputColor;
}

void sempRT::TextureBase::SetTransformMatrix(const qbVector<double> &translation, const double &rotation, const qbVector<double> &scale)
{
	qbMatrix2<double> rotationMatrix = {3, 3, std::vector<double> {
																			cos(rotation), -sin(rotation), 0.0,
																			sin(rotation), cos(rotation), 0.0,
																			0.0, 0.0, 1.0}};
																			
	qbMatrix2<double> scaleMatrix = {	3, 3, std::vector<double> {
																		scale.GetElement(0), 0.0, 0.0,
																		0.0, scale.GetElement(1), 0.0,
																		0.0, 0.0, 1.0}};																		
	qbMatrix2<double> translationMatrix = {	3, 3, std::vector<double> {
																					1.0, 0.0, translation.GetElement(0),
																					0.0, 1.0, translation.GetElement(1),
																					0.0, 0.0, 1.0}};
																					
	m_transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

qbVector<double> sempRT::TextureBase::ApplyTransform(const qbVector<double> &point)
{
	qbVector<double> newInput {3};
	newInput.SetElement(0, point.GetElement(0));
	newInput.SetElement(1, point.GetElement(1));
	
	qbVector<double> result = m_transformMatrix * newInput;
	
	qbVector<double> output {2};
	output.SetElement(0, result.GetElement(0));
	output.SetElement(1, result.GetElement(1));
	
	return output;}

qbVector<double> sempRT::TextureBase::BlendColors(const std::vector<qbVector<double>> &colors)
{
   qbVector<double> outputColor {3};
	
	// Return the output.
	return outputColor;}
