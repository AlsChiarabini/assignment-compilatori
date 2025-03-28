; ModuleID = 'test2.cpp'
source_filename = "test2.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx15.0.0"

; Function Attrs: mustprogress noinline norecurse nounwind ssp uwtable
define noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 3, ptr %2, align 4
  store i32 8, ptr %3, align 4
  store i32 16, ptr %4, align 4
  store i32 8, ptr %5, align 4
  store i32 7, ptr %6, align 4
  store i32 9, ptr %7, align 4
  %12 = load i32, ptr %2, align 4
  %13 = load i32, ptr %4, align 4
  %14 = mul nsw i32 %12, %13
  store i32 %14, ptr %8, align 4
  %15 = load i32, ptr %3, align 4
  %16 = load i32, ptr %5, align 4
  %17 = sdiv i32 %15, %16
  store i32 %17, ptr %9, align 4
  %18 = load i32, ptr %2, align 4
  %19 = load i32, ptr %6, align 4
  %20 = mul nsw i32 %18, %19
  store i32 %20, ptr %10, align 4
  %21 = load i32, ptr %2, align 4
  %22 = load i32, ptr %7, align 4
  %23 = mul nsw i32 %21, %22
  store i32 %23, ptr %11, align 4
  %24 = load i32, ptr %8, align 4
  %25 = load i32, ptr %9, align 4
  %26 = add nsw i32 %24, %25
  %27 = load i32, ptr %10, align 4
  %28 = add nsw i32 %26, %27
  %29 = load i32, ptr %11, align 4
  %30 = add nsw i32 %28, %29
  ret i32 %30
}

attributes #0 = { mustprogress noinline norecurse nounwind ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Homebrew clang version 19.1.7"}
