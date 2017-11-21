(module
 (type $FUNCSIG$ijji (func (param i64 i64 i32) (result i32)))
 (type $FUNCSIG$ijjii (func (param i64 i64 i32 i32) (result i32)))
 (type $FUNCSIG$vj (func (param i64)))
 (type $FUNCSIG$ijjjii (func (param i64 i64 i64 i32 i32) (result i32)))
 (type $FUNCSIG$vii (func (param i32 i32)))
 (type $FUNCSIG$vi (func (param i32)))
 (type $FUNCSIG$iii (func (param i32 i32) (result i32)))
 (import "env" "assert" (func $assert (param i32 i32)))
 (import "env" "load_i64" (func $load_i64 (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "printi" (func $printi (param i64)))
 (import "env" "printn" (func $printn (param i64)))
 (import "env" "prints" (func $prints (param i32)))
 (import "env" "read_message" (func $read_message (param i32 i32) (result i32)))
 (import "env" "remove_i64" (func $remove_i64 (param i64 i64 i32) (result i32)))
 (import "env" "require_auth" (func $require_auth (param i64)))
 (import "env" "require_notice" (func $require_notice (param i64)))
 (import "env" "store_i64" (func $store_i64 (param i64 i64 i32 i32) (result i32)))
 (table 0 anyfunc)
 (memory $0 1)
 (data (i32.const 4) "\f0A\00\00")
 (data (i32.const 16) "account\00")
 (data (i32.const 32) "integer underflow subtracting token balance\00")
 (data (i32.const 80) "integer overflow adding token balance\00")
 (data (i32.const 128) "currency\00")
 (data (i32.const 144) "init currency contract: \00")
 (data (i32.const 176) "N(currency): \00")
 (data (i32.const 192) "\n\00")
 (data (i32.const 208) "name(code).value\00")
 (data (i32.const 240) "code: \00")
 (data (i32.const 256) "; name(code): \00")
 (data (i32.const 272) " name(code).value: \00")
 (data (i32.const 304) " N(name(code).value): \00")
 (data (i32.const 336) "action: \00")
 (data (i32.const 352) "; name(action): \00")
 (data (i32.const 384) "transfer\00")
 (data (i32.const 400) "message shorter than expected\00")
 (data (i32.const 432) "Transfer \00")
 (data (i32.const 448) " \00")
 (data (i32.const 464) " from \00")
 (data (i32.const 480) " to \00")
 (export "memory" (memory $0))
 (export "_ZN8currency13store_accountEyRKNS_7accountE" (func $_ZN8currency13store_accountEyRKNS_7accountE))
 (export "_ZN8currency23apply_currency_transferERKNS_8transferE" (func $_ZN8currency23apply_currency_transferERKNS_8transferE))
 (export "init" (func $init))
 (export "apply12" (func $apply12))
 (export "apply" (func $apply))
 (func $_ZN8currency13store_accountEyRKNS_7accountE (param $0 i64) (param $1 i32)
  (block $label$0
   (br_if $label$0
    (i64.eq
     (i64.load offset=8
      (get_local $1)
     )
     (i64.const 0)
    )
   )
   (drop
    (call $store_i64
     (get_local $0)
     (i64.const 3607749778735104000)
     (get_local $1)
     (i32.const 16)
    )
   )
   (return)
  )
  (drop
   (call $remove_i64
    (get_local $0)
    (i64.const 3607749778735104000)
    (get_local $1)
   )
  )
 )
 (func $_ZN8currency23apply_currency_transferERKNS_8transferE (param $0 i32)
  (local $1 i64)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 i64)
  (local $7 i64)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (set_local $5
   (i64.load
    (get_local $0)
   )
  )
  (call $require_notice
   (i64.load offset=8
    (get_local $0)
   )
  )
  (call $require_notice
   (get_local $5)
  )
  (call $require_auth
   (i64.load
    (get_local $0)
   )
  )
  (set_local $1
   (i64.load
    (get_local $0)
   )
  )
  (set_local $5
   (i64.const 0)
  )
  (set_local $4
   (i64.const 59)
  )
  (set_local $3
   (i32.const 16)
  )
  (set_local $6
   (i64.const 0)
  )
  (loop $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (br_if $label$5
         (i64.gt_u
          (get_local $5)
          (i64.const 6)
         )
        )
        (br_if $label$4
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $2
             (i32.load8_s
              (get_local $3)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $2
         (i32.add
          (get_local $2)
          (i32.const 165)
         )
        )
        (br $label$3)
       )
       (set_local $7
        (i64.const 0)
       )
       (br_if $label$2
        (i64.le_u
         (get_local $5)
         (i64.const 11)
        )
       )
       (br $label$1)
      )
      (set_local $2
       (select
        (i32.add
         (get_local $2)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $2)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $7
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $2)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $7
     (i64.shl
      (i64.and
       (get_local $7)
       (i64.const 31)
      )
      (i64.and
       (get_local $4)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $3
    (i32.add
     (get_local $3)
     (i32.const 1)
    )
   )
   (set_local $5
    (i64.add
     (get_local $5)
     (i64.const 1)
    )
   )
   (set_local $6
    (i64.or
     (get_local $7)
     (get_local $6)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $4
      (i64.add
       (get_local $4)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (set_local $5
   (i64.const 0)
  )
  (i64.store offset=24
   (get_local $8)
   (i64.const 0)
  )
  (i64.store offset=16
   (get_local $8)
   (get_local $6)
  )
  (drop
   (call $load_i64
    (get_local $1)
    (i64.const 5093418677655568384)
    (i64.const 3607749778735104000)
    (i32.add
     (get_local $8)
     (i32.const 16)
    )
    (i32.const 16)
   )
  )
  (set_local $1
   (i64.load
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
   )
  )
  (set_local $4
   (i64.const 59)
  )
  (set_local $3
   (i32.const 16)
  )
  (set_local $6
   (i64.const 0)
  )
  (loop $label$6
   (block $label$7
    (block $label$8
     (block $label$9
      (block $label$10
       (block $label$11
        (br_if $label$11
         (i64.gt_u
          (get_local $5)
          (i64.const 6)
         )
        )
        (br_if $label$10
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $2
             (i32.load8_s
              (get_local $3)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $2
         (i32.add
          (get_local $2)
          (i32.const 165)
         )
        )
        (br $label$9)
       )
       (set_local $7
        (i64.const 0)
       )
       (br_if $label$8
        (i64.le_u
         (get_local $5)
         (i64.const 11)
        )
       )
       (br $label$7)
      )
      (set_local $2
       (select
        (i32.add
         (get_local $2)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $2)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $7
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $2)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $7
     (i64.shl
      (i64.and
       (get_local $7)
       (i64.const 31)
      )
      (i64.and
       (get_local $4)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $3
    (i32.add
     (get_local $3)
     (i32.const 1)
    )
   )
   (set_local $5
    (i64.add
     (get_local $5)
     (i64.const 1)
    )
   )
   (set_local $6
    (i64.or
     (get_local $7)
     (get_local $6)
    )
   )
   (br_if $label$6
    (i64.ne
     (tee_local $4
      (i64.add
       (get_local $4)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (i64.store
   (get_local $8)
   (get_local $6)
  )
  (i64.store offset=8
   (get_local $8)
   (i64.const 0)
  )
  (drop
   (call $load_i64
    (get_local $1)
    (i64.const 5093418677655568384)
    (i64.const 3607749778735104000)
    (get_local $8)
    (i32.const 16)
   )
  )
  (call $assert
   (i64.ge_u
    (i64.load
     (tee_local $3
      (i32.add
       (get_local $8)
       (i32.const 24)
      )
     )
    )
    (i64.load offset=16
     (get_local $0)
    )
   )
   (i32.const 32)
  )
  (i64.store
   (get_local $3)
   (i64.sub
    (i64.load
     (get_local $3)
    )
    (tee_local $5
     (i64.load offset=16
      (get_local $0)
     )
    )
   )
  )
  (call $assert
   (i64.ge_u
    (i64.add
     (get_local $5)
     (i64.load offset=8
      (get_local $8)
     )
    )
    (get_local $5)
   )
   (i32.const 80)
  )
  (i64.store offset=8
   (get_local $8)
   (i64.add
    (i64.load offset=8
     (get_local $8)
    )
    (i64.load offset=16
     (get_local $0)
    )
   )
  )
  (set_local $5
   (i64.load
    (get_local $0)
   )
  )
  (block $label$12
   (block $label$13
    (br_if $label$13
     (i64.eq
      (i64.load
       (get_local $3)
      )
      (i64.const 0)
     )
    )
    (drop
     (call $store_i64
      (get_local $5)
      (i64.const 3607749778735104000)
      (i32.add
       (get_local $8)
       (i32.const 16)
      )
      (i32.const 16)
     )
    )
    (br $label$12)
   )
   (drop
    (call $remove_i64
     (get_local $5)
     (i64.const 3607749778735104000)
     (i32.add
      (get_local $8)
      (i32.const 16)
     )
    )
   )
  )
  (set_local $5
   (i64.load
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
   )
  )
  (block $label$14
   (block $label$15
    (br_if $label$15
     (i64.eq
      (i64.load
       (i32.add
        (get_local $8)
        (i32.const 8)
       )
      )
      (i64.const 0)
     )
    )
    (drop
     (call $store_i64
      (get_local $5)
      (i64.const 3607749778735104000)
      (get_local $8)
      (i32.const 16)
     )
    )
    (br $label$14)
   )
   (drop
    (call $remove_i64
     (get_local $5)
     (i64.const 3607749778735104000)
     (get_local $8)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 32)
   )
  )
 )
 (func $init
  (local $0 i32)
  (local $1 i32)
  (local $2 i64)
  (local $3 i64)
  (local $4 i64)
  (local $5 i64)
  (local $6 i64)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $3
   (i64.const 0)
  )
  (set_local $2
   (i64.const 59)
  )
  (set_local $1
   (i32.const 128)
  )
  (set_local $4
   (i64.const 0)
  )
  (loop $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (br_if $label$5
         (i64.gt_u
          (get_local $3)
          (i64.const 7)
         )
        )
        (br_if $label$4
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $0
             (i32.load8_s
              (get_local $1)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $0
         (i32.add
          (get_local $0)
          (i32.const 165)
         )
        )
        (br $label$3)
       )
       (set_local $5
        (i64.const 0)
       )
       (br_if $label$2
        (i64.le_u
         (get_local $3)
         (i64.const 11)
        )
       )
       (br $label$1)
      )
      (set_local $0
       (select
        (i32.add
         (get_local $0)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $0)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $5
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $0)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $5
     (i64.shl
      (i64.and
       (get_local $5)
       (i64.const 31)
      )
      (i64.and
       (get_local $2)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $1
    (i32.add
     (get_local $1)
     (i32.const 1)
    )
   )
   (set_local $3
    (i64.add
     (get_local $3)
     (i64.const 1)
    )
   )
   (set_local $4
    (i64.or
     (get_local $5)
     (get_local $4)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $2
      (i64.add
       (get_local $2)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (call $prints
   (i32.const 144)
  )
  (call $prints
   (i32.const 176)
  )
  (call $printi
   (get_local $4)
  )
  (call $prints
   (i32.const 192)
  )
  (set_local $3
   (i64.const 0)
  )
  (set_local $2
   (i64.const 59)
  )
  (set_local $1
   (i32.const 128)
  )
  (set_local $4
   (i64.const 0)
  )
  (loop $label$6
   (block $label$7
    (block $label$8
     (block $label$9
      (block $label$10
       (block $label$11
        (br_if $label$11
         (i64.gt_u
          (get_local $3)
          (i64.const 7)
         )
        )
        (br_if $label$10
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $0
             (i32.load8_s
              (get_local $1)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $0
         (i32.add
          (get_local $0)
          (i32.const 165)
         )
        )
        (br $label$9)
       )
       (set_local $5
        (i64.const 0)
       )
       (br_if $label$8
        (i64.le_u
         (get_local $3)
         (i64.const 11)
        )
       )
       (br $label$7)
      )
      (set_local $0
       (select
        (i32.add
         (get_local $0)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $0)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $5
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $0)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $5
     (i64.shl
      (i64.and
       (get_local $5)
       (i64.const 31)
      )
      (i64.and
       (get_local $2)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $1
    (i32.add
     (get_local $1)
     (i32.const 1)
    )
   )
   (set_local $3
    (i64.add
     (get_local $3)
     (i64.const 1)
    )
   )
   (set_local $4
    (i64.or
     (get_local $5)
     (get_local $4)
    )
   )
   (br_if $label$6
    (i64.ne
     (tee_local $2
      (i64.add
       (get_local $2)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (set_local $3
   (i64.const 0)
  )
  (set_local $2
   (i64.const 59)
  )
  (set_local $1
   (i32.const 16)
  )
  (set_local $6
   (i64.const 0)
  )
  (loop $label$12
   (block $label$13
    (block $label$14
     (block $label$15
      (block $label$16
       (block $label$17
        (br_if $label$17
         (i64.gt_u
          (get_local $3)
          (i64.const 6)
         )
        )
        (br_if $label$16
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $0
             (i32.load8_s
              (get_local $1)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $0
         (i32.add
          (get_local $0)
          (i32.const 165)
         )
        )
        (br $label$15)
       )
       (set_local $5
        (i64.const 0)
       )
       (br_if $label$14
        (i64.le_u
         (get_local $3)
         (i64.const 11)
        )
       )
       (br $label$13)
      )
      (set_local $0
       (select
        (i32.add
         (get_local $0)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $0)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $5
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $0)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $5
     (i64.shl
      (i64.and
       (get_local $5)
       (i64.const 31)
      )
      (i64.and
       (get_local $2)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $1
    (i32.add
     (get_local $1)
     (i32.const 1)
    )
   )
   (set_local $3
    (i64.add
     (get_local $3)
     (i64.const 1)
    )
   )
   (set_local $6
    (i64.or
     (get_local $5)
     (get_local $6)
    )
   )
   (br_if $label$12
    (i64.ne
     (tee_local $2
      (i64.add
       (get_local $2)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (i64.store offset=8
   (get_local $7)
   (i64.const 1000000000)
  )
  (i64.store
   (get_local $7)
   (get_local $6)
  )
  (drop
   (call $store_i64
    (get_local $4)
    (i64.const 3607749778735104000)
    (get_local $7)
    (i32.const 16)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 16)
   )
  )
 )
 (func $apply12 (param $0 i64) (param $1 i64)
 )
 (func $apply (param $0 i64) (param $1 i64)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 i64)
  (local $7 i64)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (set_local $4
   (i64.const 0)
  )
  (set_local $6
   (i64.const 59)
  )
  (set_local $3
   (i32.const 208)
  )
  (set_local $5
   (i64.const 0)
  )
  (loop $label$0
   (set_local $7
    (i64.const 0)
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i64.gt_u
       (get_local $4)
       (i64.const 15)
      )
     )
     (block $label$3
      (block $label$4
       (br_if $label$4
        (i32.gt_u
         (i32.and
          (i32.add
           (tee_local $2
            (i32.load8_s
             (get_local $3)
            )
           )
           (i32.const -97)
          )
          (i32.const 255)
         )
         (i32.const 25)
        )
       )
       (set_local $2
        (i32.add
         (get_local $2)
         (i32.const 165)
        )
       )
       (br $label$3)
      )
      (set_local $2
       (select
        (i32.add
         (get_local $2)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $2)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $7
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $2)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
     (br_if $label$2
      (i64.gt_u
       (get_local $4)
       (i64.const 11)
      )
     )
     (set_local $7
      (i64.shl
       (i64.and
        (get_local $7)
        (i64.const 31)
       )
       (i64.and
        (get_local $6)
        (i64.const 4294967295)
       )
      )
     )
     (br $label$1)
    )
    (set_local $7
     (i64.and
      (get_local $7)
      (i64.const 15)
     )
    )
   )
   (set_local $3
    (i32.add
     (get_local $3)
     (i32.const 1)
    )
   )
   (set_local $4
    (i64.add
     (get_local $4)
     (i64.const 1)
    )
   )
   (set_local $5
    (i64.or
     (get_local $7)
     (get_local $5)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $6
      (i64.add
       (get_local $6)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (call $_ZN5eosio5printIPKcJyS2_NS_4nameES2_yS2_yS2_S2_yS2_S3_S2_EEEvT_DpT0_
   (i32.const 240)
   (get_local $0)
   (i32.const 256)
   (get_local $0)
   (i32.const 272)
   (get_local $0)
   (i32.const 304)
   (get_local $5)
   (i32.const 192)
   (i32.const 336)
   (get_local $1)
   (i32.const 352)
   (get_local $1)
   (i32.const 192)
  )
  (set_local $4
   (i64.const 0)
  )
  (set_local $6
   (i64.const 59)
  )
  (set_local $3
   (i32.const 128)
  )
  (set_local $5
   (i64.const 0)
  )
  (loop $label$5
   (block $label$6
    (block $label$7
     (block $label$8
      (block $label$9
       (block $label$10
        (br_if $label$10
         (i64.gt_u
          (get_local $4)
          (i64.const 7)
         )
        )
        (br_if $label$9
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $2
             (i32.load8_s
              (get_local $3)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $2
         (i32.add
          (get_local $2)
          (i32.const 165)
         )
        )
        (br $label$8)
       )
       (set_local $7
        (i64.const 0)
       )
       (br_if $label$7
        (i64.le_u
         (get_local $4)
         (i64.const 11)
        )
       )
       (br $label$6)
      )
      (set_local $2
       (select
        (i32.add
         (get_local $2)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $2)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $7
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $2)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $7
     (i64.shl
      (i64.and
       (get_local $7)
       (i64.const 31)
      )
      (i64.and
       (get_local $6)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $3
    (i32.add
     (get_local $3)
     (i32.const 1)
    )
   )
   (set_local $4
    (i64.add
     (get_local $4)
     (i64.const 1)
    )
   )
   (set_local $5
    (i64.or
     (get_local $7)
     (get_local $5)
    )
   )
   (br_if $label$5
    (i64.ne
     (tee_local $6
      (i64.add
       (get_local $6)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (block $label$11
   (br_if $label$11
    (i64.ne
     (get_local $5)
     (get_local $0)
    )
   )
   (set_local $4
    (i64.const 0)
   )
   (set_local $6
    (i64.const 59)
   )
   (set_local $3
    (i32.const 384)
   )
   (set_local $5
    (i64.const 0)
   )
   (loop $label$12
    (block $label$13
     (block $label$14
      (block $label$15
       (block $label$16
        (block $label$17
         (br_if $label$17
          (i64.gt_u
           (get_local $4)
           (i64.const 7)
          )
         )
         (br_if $label$16
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $2
              (i32.load8_s
               (get_local $3)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $2
          (i32.add
           (get_local $2)
           (i32.const 165)
          )
         )
         (br $label$15)
        )
        (set_local $7
         (i64.const 0)
        )
        (br_if $label$14
         (i64.le_u
          (get_local $4)
          (i64.const 11)
         )
        )
        (br $label$13)
       )
       (set_local $2
        (select
         (i32.add
          (get_local $2)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $2)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $7
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $2)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $7
      (i64.shl
       (i64.and
        (get_local $7)
        (i64.const 31)
       )
       (i64.and
        (get_local $6)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $3
     (i32.add
      (get_local $3)
      (i32.const 1)
     )
    )
    (set_local $4
     (i64.add
      (get_local $4)
      (i64.const 1)
     )
    )
    (set_local $5
     (i64.or
      (get_local $7)
      (get_local $5)
     )
    )
    (br_if $label$12
     (i64.ne
      (tee_local $6
       (i64.add
        (get_local $6)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (br_if $label$11
    (i64.ne
     (get_local $5)
     (get_local $1)
    )
   )
   (i64.store offset=40
    (get_local $8)
    (i64.const 0)
   )
   (call $assert
    (i32.gt_u
     (call $read_message
      (i32.add
       (get_local $8)
       (i32.const 24)
      )
      (i32.const 24)
     )
     (i32.const 23)
    )
    (i32.const 400)
   )
   (set_local $4
    (i64.load offset=32
     (get_local $8)
    )
   )
   (set_local $7
    (i64.load offset=24
     (get_local $8)
    )
   )
   (set_local $6
    (i64.load offset=40
     (get_local $8)
    )
   )
   (call $prints
    (i32.const 432)
   )
   (call $printi
    (get_local $6)
   )
   (call $prints
    (i32.const 448)
   )
   (call $printn
    (i64.const 5093418677655568384)
   )
   (call $prints
    (i32.const 464)
   )
   (call $printi
    (get_local $7)
   )
   (call $prints
    (i32.const 480)
   )
   (call $printi
    (get_local $4)
   )
   (call $prints
    (i32.const 192)
   )
   (i64.store offset=16
    (get_local $8)
    (i64.const 0)
   )
   (call $assert
    (i32.gt_u
     (call $read_message
      (get_local $8)
      (i32.const 24)
     )
     (i32.const 23)
    )
    (i32.const 400)
   )
   (call $_ZN8currency23apply_currency_transferERKNS_8transferE
    (get_local $8)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 48)
   )
  )
 )
 (func $_ZN5eosio5printIPKcJyS2_NS_4nameES2_yS2_yS2_S2_yS2_S3_S2_EEEvT_DpT0_ (param $0 i32) (param $1 i64) (param $2 i32) (param $3 i64) (param $4 i32) (param $5 i64) (param $6 i32) (param $7 i64) (param $8 i32) (param $9 i32) (param $10 i64) (param $11 i32) (param $12 i64) (param $13 i32)
  (call $prints
   (get_local $0)
  )
  (call $printi
   (get_local $1)
  )
  (call $prints
   (get_local $2)
  )
  (call $printn
   (get_local $3)
  )
  (call $prints
   (get_local $4)
  )
  (call $printi
   (get_local $5)
  )
  (call $prints
   (get_local $6)
  )
  (call $printi
   (get_local $7)
  )
  (call $prints
   (get_local $8)
  )
  (call $prints
   (get_local $9)
  )
  (call $printi
   (get_local $10)
  )
  (call $prints
   (get_local $11)
  )
  (call $printn
   (get_local $12)
  )
  (call $prints
   (get_local $13)
  )
 )
)
