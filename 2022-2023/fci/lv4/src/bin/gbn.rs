// TODO: VEDI `fn go_back_n_nack`
// TODO: SISTEMA PER FARLO FUNZIONARE SU PIU' COLLEGAMENTI
//
fn main() {
    // 7
    let capacity_andata = 10e9;
    let capacity_ritorno = 10e9;
    let distanza = 16.0; // [m] (vedi sotto)
    let propagation_time = distanza * 5e-9; // fibra: metri * costante
    let file_dim = 375.0 * 8.0;
    let mss = 60.0 * 8.0;
    let header = 10.0 * 8.0;
    let ack = header;
    let window_size = 4.0;
    let lost = vec![];

    //9
    /* let capacity_andata = vec![160e6];
    let capacity_ritorno = capacity_andata.clone();
    let distanza = 4e6f64; // [m] (vedi sotto)
    let propagation_time = vec![distanza * 5e-9]; // fibra: metri * costante
    let file_dim = (125000 * 9 + 80000) as f64 * 8.0;
    let mss = 125080.0 * 8.0;
    let ack = 80.0 * 8.0;
    let header = ack;
    let window_size = 5.0;
    let lost = vec![4]; */

    let time = go_back_n_nack(
        capacity_andata,
        capacity_ritorno,
        mss,
        ack,
        propagation_time,
        file_dim,
        header,
        window_size,
        &lost,
    );
    println!("Go Back N: {} ms", time * 1e3);
    let thr = file_dim / time;
    println!("THR : {} kbit/s", thr / 1e3);
    let eff = thr / capacity_andata;
    println!("eff : {} kbit/s", eff * 1e2);
}

fn go_back_n(
    capacity_andata: f64,
    capacity_ritorno: f64,
    mss: f64,
    ack: f64,
    propagation_time: f64,
    file_dim: f64,
    header: f64,
    window_size: f64,
    flag: bool,
) -> f64 {
    let mut n_pack = (file_dim / (mss - header)).floor();
    let mut extra = file_dim - (n_pack * (mss - header));
    if extra > 1e-12 {
        extra += header;
    } else {
        extra = mss;
        n_pack -= 1.0;
    }

    let transmission_time_mss = mss / capacity_andata;
    let transmission_time_ext = extra / capacity_andata;
    let transmission_time_ack = ack / capacity_ritorno;
    let rtt_mss = transmission_time_mss + transmission_time_ack + propagation_time * 2f64;
    let rtt_extra = rtt_mss - transmission_time_mss + transmission_time_ext;
    dbg!(rtt_mss, rtt_extra);

    let time;
    // e' continua ?
    if rtt_mss - window_size * transmission_time_mss <= 1e-12 {
        time = n_pack * transmission_time_mss + rtt_extra;
    } else {
        if flag {
            let better_window_size = (rtt_mss / transmission_time_mss).ceil();
            let time_2 = go_back_n(
                capacity_andata,
                capacity_ritorno,
                mss,
                ack,
                propagation_time,
                file_dim,
                header,
                better_window_size,
                true,
            );
            println!(
                "With better window size ({}) : {} ms",
                better_window_size,
                time_2 * 1e3
            );
        }
        let number_of_rtt = (n_pack / window_size).floor();
        let leftover_pack = n_pack - window_size * number_of_rtt;
        time = number_of_rtt * rtt_mss + leftover_pack * transmission_time_mss + rtt_extra
    }
    time
}

fn go_back_n_nack(
    capacity_andata: f64,
    capacity_ritorno: f64,
    mss: f64,
    ack: f64,
    propagation_time: f64,
    mut file_dim: f64,
    header: f64,
    window_size: f64,
    lost: &Vec<u64>,
) -> f64 {
    // se capita di dover usare il timeout lo sistemo a mano:
    // stampo l'rtt e ...
    // ris = ris - (rtt - timeout) * n_pack_lost ... attento se viene perso l'ultimo usa rtte
    // al momento ho di meglio da fare...

    let mut time = 0f64;
    lost.iter().fold(0, |a, b| b - a);
    for lost in lost {
        let first_pack = (mss - header) * (lost + 1) as f64;
        time += go_back_n(
            capacity_andata,
            capacity_ritorno,
            mss,
            ack,
            propagation_time,
            first_pack,
            header,
            window_size,
            false,
        );
        file_dim = file_dim - first_pack + 2.0 * (mss - header);
    }
    time += go_back_n(
        capacity_andata,
        capacity_ritorno,
        mss,
        ack,
        propagation_time,
        file_dim,
        header,
        window_size,
        false,
    );

    time
}
