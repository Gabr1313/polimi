// LIMITAZIONI 
// il programma accetta errori sono nella prima trasmissione di un pacchetto,
// (non nelle successive e non negli ack)
// algoritmi di Karn e Jacobson non sono implementati
// algoritmi di fast retransmit e fast recovery non sono implementati
// la rcwdn non puo' variare a runtime

// PER L'UTILIZZO
// negli errori, per mettere l'ultimo pacchetto scrivere `0`, penultimo `-1` etc.

// PER L'ANALISI
// per comprendere il programma consiglio di eliminare inizialmente la parte riguardante gli errori

fn main() {
    // 14
    // il prof non considera apertura connessione
    /* let header = 0 * 8;
    let ack = 0 * 8;
    let rcwnd = 40;
    let mss = 100 * 8;
    let ssthresh = 4;
    let file_dim = 1_000 * 8;
    let c = vec![40e6, 80e6];
    let tau = vec![1e-6; 2];
    let err = vec![];
    let mut timeout = 3.0; */

    // 15
    /* let header = 0 * 8;
    let ack = 0 * 8;
    let rcwnd = i64::MAX;
    let mss = 1000;
    let ssthresh = 5;
    let file_dim = mss * 100;
    let c = vec![1e6];
    let tau = vec![3.1e-3];
    let err = vec![];
    let mut timeout = 3.0; */

    // 16
    /* let header = 0 * 8;
    let ack = 20 * 8;
    let rcwnd = 20;
    let mss = 200 * 8;
    let ssthresh = 2;
    let file_dim = 2_000 * 8;
    let c = vec![25e3, 50e3, 100e3];
    let tau = vec![15e-3; 3];
    let err = vec![];
    let mut timeout = 3.0; */

    // 21
    /* let header = 200 * 8;
    let ack = 350 * 8;
    let rcwnd = i64::MAX;
    let mss = 1200 * 8;
    let ssthresh = (60_000 * 8) / mss;
    let file_dim = 60_850 * 8;
    let c = vec![560e3, 2.8e6];
    let tau = vec![30e-3, 30e-3];
    // let err = vec![];
    let err = vec![-1, 0]; // penultimo e ultimo
    let mut timeout = -1.0; */

    // 22
    /* let header = 0 * 8;
    let ack = 0 * 8;
    let rcwnd = 16;
    let mss = 1000 * 8;
    let ssthresh = 8;
    let file_dim = 80_000 * 8;
    let c = vec![8e6];
    let tau = vec![5e-3];
    let err = vec![6]; // sesto, non settimo
    let mut timeout = 3.0; */

    // 24
    /* let header = 0 * 8;
    let ack = 0 * 8;
    let rcwnd = 16;
    let mss = 1000 * 8;
    let ssthresh = 8;
    let file_dim = 80_000 * 8;
    let c = vec![8e6];
    let tau = vec![5e-3];
    // let err = vec![];
    let err = vec![0]; // ultimo
    let mut timeout = 3.0; */

    // 25
    /* let header = 50 * 8;
    let ack = 250 * 8;
    let rcwnd = 5;
    let mss = 200 * 8;
    let ssthresh = 8;
    let file_dim = 5_000 * 8;
    let c = vec![200e3, 400e3];
    let tau = vec![ 20e-3, 20e-3];
    let err = vec![];
    let mut timeout = 0.0; */

    // 27
    /* let header = 0;
    let ack = 0;
    let rcwnd = i64::MAX;
    let mss = 1250 * 8;
    let ssthresh = 8;
    let file_dim = 55_000 * 8;
    let tau = vec![10e-3, 5e-3, 5e-3];
    let c = vec![10e6, 2e6, 20e6];
    let err = vec![];
    let mut timeout = 0.0; */

    // 29
    /* let header = 0;
    let ack = 0;
    let rcwnd = 12;
    let mss = 100 * 8;
    let ssthresh = 4;
    let file_dim = 10_000 * 8;
    let c = vec![5e6, 10e6];
    let tau = vec![1e-3, 1e-3];
    let err = vec![3]; // terzo, non quarto
    let mut timeout = -3.0; // 3rtt */

    // 31
    /* let header = 0;
    let ack = 0;
    let rcwnd = 9;
    let mss = 1000 * 8;
    let ssthresh = 8;
    let file_dim = 60_000 * 8;
    let tau = vec![5e-3];
    let c = vec![8e6];
    let err = [-1]; // penultimo
    let mut timeout = -2.0; // 2rtt */
    
    // challenge
    let header = 0;
    let ack = 0;
    let rcwnd = 16;
    let mss = 200 * 8;
    let ssthresh = 4;
    let file_dim = 20_000 * 8;
    let tau = vec![1e-3, 1e-3];
    let c = vec![5e6, 10e6];
    let err = [];
    let mut timeout = -3.0; // 3rtt


    let mut tot_pack = file_dim / mss;
    let mut ess = file_dim % mss + header;
    let mss = mss + header;
    if ess == header {
        tot_pack -= 1;
        ess = mss;
    }

    let mut err: Vec<i64> = err
        .iter()
        .map(|&x| if x > 0 { x } else { tot_pack + 1 + x })
        .collect();
    err.sort();

    let mut tm = Vec::with_capacity(c.len());
    let mut te = Vec::with_capacity(c.len());
    let mut ta = Vec::with_capacity(c.len());
    let mut tm_max = f64::NEG_INFINITY;
    for i in 0..c.len() {
        tm.push(mss as f64 / c[i]);
        if *tm.last().unwrap() > tm_max {
            tm_max = *tm.last().unwrap();
        }
        te.push(ess as f64 / c[i]);
        ta.push(ack as f64 / c[i]);
    }
    let rtt = tm.iter().sum::<f64>() + ta.iter().sum::<f64>() + tau.iter().sum::<f64>() * 2.0;
    let rtte = te.iter().sum::<f64>() + ta.iter().sum::<f64>() + tau.iter().sum::<f64>() * 2.0;
    let cwnd = (rtt / tm_max).ceil() as i64;

    if timeout < 0.0 {
        timeout *= -rtt;
    }

    let mut time = 0.0;
    let time_setup = (ta.iter().sum::<f64>() + tau.iter().sum::<f64>()) * 2.0;
    time += time_setup;

    // per calcoli a mano, questi sicuro sono giusti e aiutano
    dbg!(tot_pack + 1);
    dbg!(rtt);
    dbg!(rtte);
    dbg!(tm_max);
    dbg!(time_setup);
    dbg!(ssthresh);
    dbg!(cwnd);
    dbg!(rcwnd);
    dbg!(timeout);
    time = tcp_time(
        time, ssthresh, tot_pack, cwnd, rcwnd, rtt, rtte, tm_max, &mut err, timeout,
    );
    println!("Tcp time: {}", time * 1e3);
}

fn tcp_time(
    mut time: f64,
    ssthresh: i64,
    tot_pack: i64,
    cwnd: i64,
    rcwnd: i64,
    rtt: f64,
    rtte: f64,
    tm_max: f64,
    err: &mut Vec<i64>,
    timeout: f64,
) -> f64 {
    let mut flying_pack = 1;
    let mut received_pack = 0;

    // slow start
    while flying_pack <= ssthresh
        && (tot_pack - received_pack) >= flying_pack
        && cwnd > flying_pack
        && rcwnd > flying_pack
    {
        time += rtt;
        received_pack += flying_pack;
        flying_pack <<= 1;

        if err.len() > 0 && err[0] <= received_pack + flying_pack {
            let pack_before = err[0] - received_pack - 1;
            let pack_after = pack_before.min(((timeout - rtt) / tm_max).ceil() as i64);
            let flight_size =
                (flying_pack + pack_after).min(tot_pack + 1 - received_pack - pack_before);

            let mut pack_arrived = pack_before + flight_size;
            let flag_1 = tot_pack == pack_arrived + received_pack;
            let flag_2 = err.contains(&(tot_pack + 1));
            for &e in err.iter() {
                if e <= received_pack + pack_before + flight_size {
                    pack_arrived -= 1;
                } else {
                    break;
                }
            }
            received_pack += pack_arrived;
            time += timeout + pack_after as f64 * tm_max;
            err.drain(0..(pack_before + flight_size - pack_arrived) as usize);
            let mut err: Vec<i64> = err.iter().map(|x| x - received_pack).collect();
            let tot_pack = tot_pack - received_pack;
            if flag_1 && !flag_2 {
                // se l'ultimo pack e' stato consegnato
                return tcp_time(
                    time,
                    2.max(flight_size / 2),
                    tot_pack - 1,
                    cwnd,
                    rcwnd,
                    rtt,
                    rtt,
                    tm_max,
                    &mut err,
                    timeout,
                );
            }
            return tcp_time(
                time,
                2.max(flight_size / 2),
                tot_pack,
                cwnd,
                rcwnd,
                rtt,
                rtte,
                tm_max,
                &mut err,
                timeout,
            );
        }
    }

    if flying_pack > ssthresh {
        // congestion avoidance
        flying_pack >>= 1;
        // il `-1` qui sotto serve perche' qui aggiorno all'interno del loop, non prima del
        // prossimo come sopra. E' comodo cosi'
        while (tot_pack - received_pack) >= flying_pack
            && cwnd - 1 > flying_pack
            && rcwnd - 1 > flying_pack
        {
            dbg!(rcwnd, flying_pack);
            flying_pack += 1;
            if err.len() > 0 && err[0] <= received_pack + flying_pack {
                // da provare con carta e penna
                let pack_before = err[0] - received_pack - 1;
                let flight_size = flying_pack.min(tot_pack + 1 - received_pack - pack_before);

                let mut pack_arrived = pack_before + flight_size;
                let flag_1 = tot_pack == pack_arrived + received_pack;
                let flag_2 = err.contains(&(tot_pack + 1));
                for &e in err.iter() {
                    if e <= received_pack + pack_before + flight_size {
                        pack_arrived -= 1;
                    } else {
                        break;
                    }
                }

                received_pack += pack_arrived;
                time += timeout + pack_before as f64 * tm_max;

                err.drain(0..(pack_before + flight_size - pack_arrived) as usize);

                let mut err: Vec<i64> = err.iter().map(|x| x - received_pack).collect();

                let tot_pack = tot_pack - received_pack;
                if flag_1 && !flag_2 {
                    // se l'ultimo pack e' stato consegnato
                    return tcp_time(
                        time,
                        2.max(flight_size / 2),
                        tot_pack - 1,
                        cwnd,
                        rcwnd,
                        rtt,
                        rtt,
                        tm_max,
                        &mut err,
                        timeout,
                    );
                }
                return tcp_time(
                    time,
                    2.max(flight_size / 2),
                    tot_pack,
                    cwnd,
                    rcwnd,
                    rtt,
                    rtte,
                    tm_max,
                    &mut err,
                    timeout,
                );
            }
            time += rtt;
            received_pack += flying_pack;
        }
        // serve per l' `rcwnd <= flying_pack`
        flying_pack += 1;
    }

    if rcwnd <= flying_pack {
        // se non e' continua
        flying_pack = rcwnd;
        while (tot_pack - received_pack) >= flying_pack {
            if err.len() > 0 && err[0] <= received_pack + flying_pack {
                // da provare con carta e penna
                let pack_before = err[0] - received_pack - 1;
                let flight_size = flying_pack.min(tot_pack + 1 - received_pack - pack_before);

                let mut pack_arrived = pack_before + flight_size;
                let flag_1 = tot_pack == pack_arrived + received_pack;
                let flag_2 = err.contains(&(tot_pack + 1));
                for &e in err.iter() {
                    if e <= received_pack + pack_before + flight_size {
                        pack_arrived -= 1;
                    } else {
                        break;
                    }
                }

                received_pack += pack_arrived;
                time += timeout + pack_before as f64 * tm_max;

                err.drain(0..(pack_before + flight_size - pack_arrived) as usize);
                let mut err: Vec<i64> = err.iter().map(|x| x - received_pack).collect();

                let tot_pack = tot_pack - received_pack;
                if flag_1 && !flag_2 {
                    // se l'ultimo pack e' stato consegnato
                    return tcp_time(
                        time,
                        2.max(flight_size / 2),
                        tot_pack - 1,
                        cwnd,
                        rcwnd,
                        rtt,
                        rtt,
                        tm_max,
                        &mut err,
                        timeout,
                    );
                }
                return tcp_time(
                    time,
                    2.max(flight_size / 2),
                    tot_pack,
                    cwnd,
                    rcwnd,
                    rtt,
                    rtte,
                    tm_max,
                    &mut err,
                    timeout,
                );
            }

            time += rtt;
            received_pack += flying_pack;
        }
    } else if tot_pack != received_pack {
        println!("continuos: {} ms", time * 1e3)
    }

    if err.len() != 0 {
        if err[0] == tot_pack + 1 {
            time += (tot_pack - received_pack) as f64 * tm_max + timeout + rtte;
        } else {
            let pack_before = err[0] - received_pack - 1;
            let flight_size = tot_pack - received_pack - pack_before + 1;

            let mut pack_arrived = pack_before + flight_size;
            let flag_1 = tot_pack == pack_arrived + received_pack;
            let flag_2 = err.contains(&(tot_pack + 1));
            for &e in err.iter() {
                if e <= received_pack + pack_before + flight_size {
                    pack_arrived -= 1;
                } else {
                    break;
                }
            }
            received_pack += pack_arrived;
            time += timeout + pack_before as f64 * tm_max;
            err.drain(0..(pack_before + flight_size - pack_arrived) as usize);
            let mut err: Vec<i64> = err.iter().map(|x| x - received_pack).collect();
            let tot_pack = tot_pack - received_pack;

            if flag_1 && !flag_2 {
                // se l'ultimo pack e' stato consegnato
                return tcp_time(
                    time,
                    2.max(flight_size / 2),
                    tot_pack - 1,
                    cwnd,
                    rcwnd,
                    rtt,
                    rtt,
                    tm_max,
                    &mut err,
                    timeout,
                );
            }
            return tcp_time(
                time,
                2.max(flight_size / 2),
                tot_pack,
                cwnd,
                rcwnd,
                rtt,
                rtte,
                tm_max,
                &mut err,
                timeout,
            );
        }
    } else {
        time += (tot_pack - received_pack) as f64 * tm_max + rtte;
    }
    time
}
