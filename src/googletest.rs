use serde::{Deserialize, Serialize};
use std::env;

#[derive(Serialize, Deserialize, Debug)]
pub struct TestResult {
    pub tests: u32,
    pub failures: u32,
    pub disabled: u32,
    pub errors: u32,
    pub timestamp: String,
    pub time: String,
    pub name: String,
    pub testsuites: Vec<TestSuite>,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct TestSuite {
    pub name: String,
    pub tests: u32,
    pub failures: u32,
    pub disabled: u32,
    pub errors: u32,
    pub timestamp: String,
    pub time: String,
    pub testsuite: Vec<TestCase>,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct TestCase {
    pub name: String,
    pub file: String,
    pub line: u32,
    pub status: String,
    pub result: String,
    pub timestamp: String,
    pub time: String,
    pub classname: String,
    pub failures: Option<Vec<Failure>>,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Failure {
    failure: String,
    r#type: String,
}

pub fn print_test_results(num: u32, name: &String, test_suite: &Vec<TestCase>) {
    println!("[==========] Running {num} tests from {num} test suites");
    println!("[----------] Global test environment set-up.");
    println!("[----------] {num} test from {name}");

    for t in test_suite {
        println!("[ RUN      ] {}", t.name);
        if t.failures.is_some() {
            let f = t.failures.as_ref().unwrap();
            let path = env::current_dir().unwrap();
            println!("[===========] Test failures from {}", f[0].failure);
            println!("[  FAILED  ] {} (0s)", t.name);
        }
        else {
            println!("[       OK ] {} (0s)", t.name);
        }
    }
}