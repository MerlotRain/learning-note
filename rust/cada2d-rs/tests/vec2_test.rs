#[cfg(test)]
mod vec2_test {
    use cada2d_rs::Vec2;

    #[test]
    fn test_constructor() {
    let v1 = Vec2::new(1.0, 2.0, None);
    assert_eq!(v1.x, 1.0);
    assert_eq!(v1.y, 2.0);
    assert_eq!(v1.valid, true);
    }

    #[test]
    fn test_angle() {
        let v1 = Vec2::new(1.0, 1.0, None);
        let angle = v1.angle();
        assert_eq!(angle, 45.0_f64.to_radians()); // Assuming angle is in radians
    }
}