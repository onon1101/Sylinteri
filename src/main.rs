mod googletest;

use std::fs;
use serde::{Deserialize, Serialize};

fn main() -> std::io::Result<()>{
    let data: String = fs::read_to_string("report.json")
        .expect("Should have been able to read the file");

    let data: &str = &data[..];

    let result: googletest::TestResult = serde_json::from_str(data)?;

    // println!("{:?}", result.tests);

    googletest::print_test_results(result.tests, &result.testsuites[0].name, &result.testsuites[0].testsuite);

    println!("[----------] 11 tests from TICKET_SYSTEM_TEST (0 s)
[----------] Global test environment tear-down.
[==========] Running 11 tests from 11 test suites (0 s total)");
    Ok(())
}
