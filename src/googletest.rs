use serde::{Deserialize, Serialize};
use std::{env, fs};

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


pub struct TestReport {
    pub filename: String,
    pub result: TestResult,
}
impl TestReport {
    pub fn new(filename: &str) -> Self {
        let json_data: String =
            fs::read_to_string(&filename).expect("Should have been able to read the file");

        let json_string_data: &str = &json_data[..];

        let json: TestResult = serde_json::from_str(json_string_data).unwrap();

        TestReport {
            filename: filename.to_string(),
            result: json,
        }
    }
    pub fn print_result(&self) {
        let result = &self.result;
        Self::init_msg(
            result.tests,
            &result.testsuites[0].name,
            &result.testsuites[0].testsuite,
        );
    }

    fn init_msg(num: u32, name: &String, test_suites: &Vec<TestCase>) {
        println!("[==========] Running {num} tests from {num} test suites");
        println!("[----------] Global test environment set-up.");
        println!("[----------] {num} test from {name}");

        for suite in test_suites {
            println!("[ RUN      ] {}", suite.name);
            if suite.failures.is_some() {
                let f = suite.failures.as_ref().unwrap();
                let path = env::current_dir().unwrap();
                println!("[===========] Test failures from {}", f[0].failure);
                println!("[  FAILED  ] {} (0s)", suite.name);
            }
            else {
                println!("[       OK ] {} (0s)", suite.name);
            }
        }

        println!("[----------]  tests from {name} (0 s)");
        println!("[----------] Global test environment tear-down.");
        println!("[==========] Running {num} tests from {num} test suites (0 s total)");
    }
}