namespace cpp uniqueid

enum ResStatus {
    kRSSuccess = 0,
    kRSFail    = 1,
    kRSAgain   = 2
}

struct UniqueidRequest {
    1: i32 logid,
    2: i32 serial,
    3: i64 length
}

struct UniqueidResponse {
    1: i32 logid,
    2: i32 serial,
    3: i64 length,
    4: i64 offset
}

exception UniqueidException {
    1: ResStatus status,
    2: string what
}

service Uniqueid {
    UniqueidResponse uniqueid(1: UniqueidRequest request) throws (1: UniqueidException ue)
}
