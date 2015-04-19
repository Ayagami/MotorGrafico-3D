#include "Vector3.h"
#include <math.h>
using namespace DoMaRe;
//---------------------------------------------
Vector3::Vector3(float x, float y, float z){
 
        this->x = x;
 
        this->y = y;
 
        this->z = z;
 
}
//---------------------------------------------
Vector3::Vector3() : x(0), y(0), z(0){
 
}
//---------------------------------------------
Vector3 Vector3::operator +(const Vector3& vector) const{
 
        return Vector3(this->x + vector.x , this->y + vector.y , this->z + vector.z);
 
}
//---------------------------------------------
Vector3& Vector3::operator +=(const Vector3& vector){
 
        x+= vector.x;
 
        y+= vector.y;
 
        z+= vector.z;
 
        return *this;
 
}
//---------------------------------------------
Vector3 Vector3::operator -(const Vector3& vector) const{
 
        return Vector3(this->x - vector.x , this->y - vector.y , this->z - vector.z);
 
}
//---------------------------------------------
Vector3& Vector3::operator -=(const Vector3& vector){
 
        x-= vector.x;
 
        y-= vector.y;
 
        z-= vector.z;
 
        return *this;
 
}
//--------------------------------------------- 
Vector3 Vector3::operator *(const float& escalar) const{
 
        return Vector3(this->x * escalar , this->y * escalar , this->z * escalar);
 
}
//---------------------------------------------
Vector3& Vector3::operator *=(const float& escalar){
 
        x*= escalar;
 
        y*= escalar;
 
        z*= escalar;
 
        return *this;
 
}
//--------------------------------------------- 
Vector3 Vector3::operator /(const float& n) const {
 
        return Vector3(this->x / n , this->y / n , this->z / n);
 
}
//---------------------------------------------
Vector3& Vector3::operator /=(const float& n){
 
        x/= n;
 
        y/= n;
 
        z/= n;
 
        return *this;
 
}
//---------------------------------------------
Vector3& Vector3::operator =(const Vector3& vector){
 
        x= vector.x;
 
        y= vector.y;
 
        z= vector.z;
 
        return *this;
 
}
//--------------------------------------------- 
bool Vector3::operator ==(const Vector3& vector) const{
 
        return (this->x == vector.x && this->y == vector.y && this->z == vector.z);
 
}
//--------------------------------------------- 
bool Vector3::operator !=( const Vector3& vector) const{
 
        return !(*this == vector);
 
}
//--------------------------------------------- 
float Vector3::GetMagnitude() const{
 
        return sqrt(x*x+y*y+z*z);
 
}
//--------------------------------------------- 
Vector3 Vector3::Normalize(){
 
        float mag = this->GetMagnitude();
 
        return Vector3(this->x / mag , this->y / mag , this->z / mag);
 
}
//---------------------------------------------