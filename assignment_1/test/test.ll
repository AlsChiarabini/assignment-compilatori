; ModuleID = 'test.ll'
source_filename = "test.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx15.0.0"

@.str = private unnamed_addr constant [18 x i8] c"Test passo 1: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [18 x i8] c"Test passo 2: %d\0A\00", align 1
@.str.2 = private unnamed_addr constant [18 x i8] c"Test passo 3: %d\0A\00", align 1
@.str.3 = private unnamed_addr constant [20 x i8] c"Test combinato: %d\0A\00", align 1

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z11test_passo1ii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 %0, 0
  %4 = add nsw i32 0, %1
  %5 = sub nsw i32 %0, 0
  %6 = mul nsw i32 %0, 1
  %7 = mul nsw i32 1, %1
  %8 = sdiv i32 %0, 1
  %9 = add nsw i32 %3, %4
  %10 = add nsw i32 %9, %5
  %11 = add nsw i32 %10, %6
  %12 = add nsw i32 %11, %7
  %13 = add nsw i32 %12, %8
  ret i32 %13
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z11test_passo2i(i32 noundef %0) #0 {
  %2 = mul nsw i32 %0, 16
  %3 = mul nsw i32 %0, 15
  %4 = mul nsw i32 %0, 17
  %5 = mul nsw i32 17, %0
  %6 = mul nsw i32 16, %0
  %7 = mul nsw i32 15, %0
  %8 = sdiv i32 %0, 8
  %9 = mul nsw i32 %0, -16
  %10 = mul nsw i32 -16, %0
  %11 = sdiv i32 %0, -8
  %12 = add nsw i32 %2, %3
  %13 = add nsw i32 %12, %4
  %14 = add nsw i32 %13, %8
  %15 = add nsw i32 %14, %9
  %16 = add nsw i32 %15, %11
  %17 = add nsw i32 %16, %5
  %18 = add nsw i32 %17, %6
  %19 = add nsw i32 %18, %7
  %20 = add nsw i32 %19, %10
  ret i32 %20
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z11test_passo3i(i32 noundef %0) #0 {
  %2 = add nsw i32 %0, 5
  %3 = sub nsw i32 %2, 5
  %4 = add nsw i32 5, %0
  %5 = sub nsw i32 %4, 5
  %6 = sub nsw i32 %0, 7
  %7 = add nsw i32 %6, 7
  %8 = add nsw i32 7, %6
  %9 = mul nsw i32 %0, 3
  %10 = sdiv i32 %9, 3
  %11 = mul nsw i32 3, %0
  %12 = sdiv i32 %11, 3
  %13 = sdiv i32 %0, 4
  %14 = mul nsw i32 %13, 4
  %15 = mul nsw i32 4, %13
  %16 = ashr i32 %0, 2
  %17 = shl i32 %16, 2
  %18 = shl i32 %0, 2
  %19 = ashr i32 %18, 2
  %20 = sdiv i32 15, 3
  %21 = add nsw i32 %3, %7
  %22 = add nsw i32 %21, %10
  %23 = add nsw i32 %22, %14
  %24 = add nsw i32 %23, %20
  %25 = add nsw i32 %24, %5
  %26 = add nsw i32 %25, %12
  %27 = add nsw i32 %26, %8
  %28 = add nsw i32 %27, %15
  %29 = add nsw i32 %28, %17
  %30 = add nsw i32 %29, %19
  ret i32 %30
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z13test_combinedii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 %0, 0
  %4 = mul nsw i32 %3, 16
  %5 = mul nsw i32 %0, 8
  %6 = sdiv i32 %5, 8
  %7 = mul nsw i32 %0, 1
  %8 = add nsw i32 %7, 10
  %9 = sub nsw i32 %8, 10
  %10 = mul nsw i32 %0, 16
  %11 = sdiv i32 %10, 2
  %12 = mul nsw i32 %11, 2
  %13 = add nsw i32 %1, 0
  %14 = mul nsw i32 %13, 1
  %15 = mul nsw i32 %14, 4
  %16 = sdiv i32 %15, 4
  %17 = add nsw i32 %4, %6
  %18 = add nsw i32 %17, %9
  %19 = add nsw i32 %18, %12
  %20 = add nsw i32 %19, %16
  ret i32 %20
}

; Function Attrs: mustprogress noinline norecurse ssp uwtable
define noundef i32 @main() #1 {
  %1 = call noundef i32 @_Z11test_passo1ii(i32 noundef 42, i32 noundef 24)
  %2 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %1)
  %3 = call noundef i32 @_Z11test_passo2i(i32 noundef 42)
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %3)
  %5 = call noundef i32 @_Z11test_passo3i(i32 noundef 42)
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %5)
  %7 = call noundef i32 @_Z13test_combinedii(i32 noundef 42, i32 noundef 24)
  %8 = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %7)
  ret i32 0
}

declare i32 @printf(ptr noundef, ...) #2

attributes #0 = { mustprogress noinline nounwind ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Homebrew clang version 19.1.7"}
