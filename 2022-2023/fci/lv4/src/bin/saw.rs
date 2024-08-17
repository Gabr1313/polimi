macro_rules! zip {
    ($x: expr) => ($x);
    ($x: expr, $($y: expr), +) => (
        $x.iter().zip(
            zip!($($y), +))
    )
}

fn main() {
    // 4
    let capacity_andata = vec![100e6, 200e6];
    let capacity_ritorno = capacity_andata.clone();
    let propagation_time = vec![500e-6, 500e-6];
    let file_dim = 1_250e6 * 8.0;
    let mss = 10000.0;
    let ack = mss;
    let header = 0.0;

    // 5
    /* let capacity_andata = vec![8e6];
    let capacity_ritorno = vec![1e6];
    let distanza = 30e3; // [m] (vedi sotto)
    let propagation_time = vec![distanza / 3e8];
    let file_dim = 480.0 * 8.0;
    let mss = 80.0 * 8.0;
    let header = 7.0 * 8.0;
    let ack = header; */

    let time = stop_and_wait(
        &capacity_andata,
        &capacity_ritorno,
        mss,
        ack,
        &propagation_time,
        file_dim,
        header,
    );
    println!("Stop and wait: {} ms", time * 1e3);
    let thr = file_dim / time;
    println!("THR: {} kbit/s", thr / 1e3);
    let eff = thr
        / capacity_andata
            .iter()
            .fold(f64::NEG_INFINITY, |a, &b| a.max(b));
    println!("eff: {} %", eff * 1e2);
    let eff = thr
        / capacity_andata
            .iter()
            .fold(f64::NEG_INFINITY, |a, &b| a.max(b));
    println!("eff: {} %", eff * 1e2);
}

fn stop_and_wait(
    capacity_andata: &Vec<f64>,
    capacity_ritorno: &Vec<f64>,
    mss: f64,
    ack: f64,
    propagation_time: &Vec<f64>,
    file_dim: f64,
    header: f64,
) -> f64 {
    let mut n_pack = (file_dim / (mss - header)).floor();
    let mut extra = file_dim - (n_pack * (mss - header));
    if extra > 1e-12 {
        extra += header;
    } else {
        extra = mss;
        n_pack -= 1.0;
    }

    let mut transmission_time_mss = Vec::with_capacity(capacity_andata.len());
    let mut transmission_time_ack = Vec::with_capacity(capacity_andata.len());
    let mut transmission_time_ext = Vec::with_capacity(capacity_andata.len());
    let mut rtt_single_line = Vec::with_capacity(capacity_andata.len());
    for (c1, (c2, p)) in zip!(capacity_andata, capacity_ritorno, propagation_time) {
        transmission_time_mss.push(mss / c1);
        transmission_time_ack.push(ack / c2);
        transmission_time_ext.push(extra / c1);
        rtt_single_line.push(mss / c1 + ack / c2 + 2.0 * p)
    }

    let mut slower = f64::NEG_INFINITY;
    let mut slower_i = 0;
    for i in 0..rtt_single_line.len() {
        if slower < rtt_single_line[i] {
            slower = rtt_single_line[i];
            slower_i = i;
        }
    }

    let mut time = 0.0;
    for i in 0..slower_i {
        time += transmission_time_mss[i] + propagation_time[i];
    }
    time += slower * n_pack;
    for i in slower_i..transmission_time_ext.len() {
        time += transmission_time_ext[i] + propagation_time[i];
    }
    println!(
        "Stop and wait senza contare l'ultimo ack: {} ms",
        time * 1e3
    );
    time += transmission_time_ack.last().unwrap() + propagation_time.last().unwrap();
    time
}
