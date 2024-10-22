mod googletest;
use googletest::TestReport;

use clap::Parser;
use serde::{Deserialize, Serialize};
use std::fs;

/// Sylinteri is an application to enhance GoogleTest result with add score calculation.
#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
struct Args {
    /// FileName of googletest to parser
    #[arg(short, long)]
    filename: String,
}

fn main() -> std::io::Result<()> {
    let args = Args::parse();
    let filename = args.filename;

    TestReport::new(&filename).print_result();

    Ok(())
}
