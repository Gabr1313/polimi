fn main () {
    // 4
    let capacity = vec![100e6, 200e6];
    let propagation_time = vec![500e-6, 500e-6];
    let file_dim = 1_250e6 * 8.0;
    let mss = 10000.0;
    let header = 0.0;
    let time = no_protocol(&capacity, mss, file_dim, header, &propagation_time);
    println!("No control: {} ms", time * 1e3);
}

fn no_protocol(
    capacity: &Vec<f64>,
    mss: f64,
    file_dim: f64,
    header: f64,
    propagation_time: &Vec<f64>,
) -> f64 {
    let mut transmission_time_mss = Vec::with_capacity(capacity.len());
    for c in capacity {
        transmission_time_mss.push(mss / c);
    }
    let slower_tt = transmission_time_mss
        .iter()
        .fold(f64::NEG_INFINITY, |a, &b| a.max(b));
    let n_pack = (file_dim / (mss - header)).floor();
    let mut dim_extra_pack = file_dim - (n_pack * (mss - header));
    let mut slower_tt_extra = 0f64;
    if dim_extra_pack > 1e-12 {
        dim_extra_pack += header;
        let mut transmission_time_ext = Vec::with_capacity(capacity.len());
        for c in capacity {
            transmission_time_ext.push(dim_extra_pack / c);
        }
        slower_tt_extra = transmission_time_ext
            .iter()
            .fold(f64::NEG_INFINITY, |a, &b| a.max(b));
    }
    let time = (n_pack - 1f64) * slower_tt
        + slower_tt_extra
        + transmission_time_mss.iter().sum::<f64>()
        + propagation_time.iter().sum::<f64>();
    time
}
