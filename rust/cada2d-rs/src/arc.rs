use super::vec2::*;

pub struct Arc {
    pub center: Vec2,
    pub radius: f64,
    pub start_angle: f64,
    pub end_angle: f64,
    pub reversed: bool,
}

impl Arc {
    pub fn new(center: Vec2, radius: f64, start_angle: f64, end_angle: f64, reversed: bool) -> Self {
        Self {
            center,
            radius,
            start_angle,
            end_angle,
            reversed,
        }
    }
}