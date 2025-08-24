use core::fmt;
use std::ops::{Add, Sub, Mul, Div, AddAssign, SubAssign, MulAssign, DivAssign, Neg};
use std::f64::consts::PI;

use crate::math_utils;

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Vec2 {
    pub x: f64,
    pub y: f64,
    pub valid: bool,
}

impl Vec2 {
    pub fn new(x: f64, y: f64, valid: Option<bool>) -> Self {
        Vec2 {
            x,
            y,
            valid: valid.unwrap_or(true),
        }
    }

    pub fn empty() -> Self {
        Vec2 {
            x: 0.0,
            y: 0.0,
            valid: true,
        }
    }

    pub fn set_polar(&mut self, radius: f64, angle: f64) {
        self.x = radius * angle.cos();
        self.y = radius * angle.sin();
        self.valid = radius.is_normal() && angle.is_normal();
    }

    pub fn equal_fuzzy(&self, other: Vec2, tolerance: Option<f64>) -> bool {
        let tol = tolerance.unwrap_or(math_utils::TOLERANCE);
        (self.x - other.x).abs() < tol
            && (self.y - other.y).abs() < tol
            && self.valid == other.valid
    }

    pub fn distance_to(&self, other: Vec2) -> f64 {
        todo!()
    }

    pub fn angle(&self)->f64 {
        todo!()
    }

    pub fn set_angle(&mut self, angle: f64) {
        todo!()
    }

    pub fn angle_to(&self, other: Vec2) -> f64 {
        todo!()
    }

    pub fn magnitude(&self) -> f64 {
        (self.x * self.x + self.y * self.y).sqrt()
    }

    pub fn set_magnitude(&mut self, magnitude: f64) {
        todo!()
    }

    pub fn lerp(&self, other: Vec2, t: f64) -> Vec2 {
        todo!()
    }

    pub fn unit_vector(&self) -> Vec2 {
        todo!()
    }
}

impl Vec2 {
    pub fn move_(&mut self, offset: Vec2) {

    }

    pub fn rotate_angle(&mut self, angle: f64) {

    }

    pub fn rotate_center(&mut self, center: Vec2, angle: f64) {

    }

    pub fn rotated(rotation: f64, center: Vec2) -> Vec2 {
        todo!()
    }

    pub fn scale(&mut self, factor: f64, center: Option<Vec2>) {
        
    }
}

impl fmt::Display for Vec2 {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "Vec2({}, {}, valid={})", self.x, self.y, self.valid)
    }
}

impl Add for Vec2 {
    type Output = Vec2;

    fn add(self, rhs: Self) -> Self::Output {
        todo!()
    }
}

impl Sub for Vec2 {
    type Output = Vec2;

    fn sub(self, rhs: Self) -> Self::Output {
        Vec2 {
            x: self.x - rhs.x,
            y: self.y - rhs.y,
            valid: self.valid && rhs.valid,
        }
    }
    
}

impl Mul<f64> for Vec2 {
    type Output = Vec2;

    fn mul(self, scale: f64) -> Self::Output {
        todo!()
    }
    
}

impl Div<f64> for Vec2 {
    type Output = Vec2;

    fn div(self, scale: f64) -> Self::Output {
        todo!()
    }
    
}

impl AddAssign for Vec2 {
    fn add_assign(&mut self, rhs: Self) {
        todo!()
    }
}

impl SubAssign for Vec2 {
    fn sub_assign(&mut self, rhs: Self) {
        self.x -= rhs.x;
        self.y -= rhs.y;
        self.valid = self.valid && rhs.valid;
    }
}

impl MulAssign<f64> for Vec2 {
    fn mul_assign(&mut self, scale: f64) {
        todo!()
    }
}

impl DivAssign<f64> for Vec2 {
    fn div_assign(&mut self, scale: f64) {
        todo!()
    }
}

impl Neg for Vec2 {
    type Output = Vec2;

    fn neg(self) -> Self::Output {
        Vec2 {
            x: -self.x,
            y: -self.y,
            valid: self.valid,
        }
    }
}