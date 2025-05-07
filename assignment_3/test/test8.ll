; ModuleID = 'test8.ll'
source_filename = "test8.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx15.0.0"

; Function Attrs: mustprogress noinline norecurse nounwind ssp uwtable
define noundef i32 @main() #0 {
  %1 = icmp sgt i32 6, 0
  br i1 %1, label %2, label %3

2:                                                ; preds = %0
  br label %4

3:                                                ; preds = %0
  br label %4

4:                                                ; preds = %3, %2
  %.01 = phi i32 [ 6, %2 ], [ 2, %3 ]
  br label %5

5:                                                ; preds = %25, %4
  %.02 = phi i32 [ 0, %4 ], [ %26, %25 ]
  %6 = icmp slt i32 %.02, 10
  br i1 %6, label %7, label %27

7:                                                ; preds = %5
  %8 = srem i32 %.02, 2
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %10, label %12

10:                                               ; preds = %7
  %11 = mul nsw i32 3, %.01
  br label %14

12:                                               ; preds = %7
  %13 = mul nsw i32 1, %.02
  br label %14

14:                                               ; preds = %12, %10
  %.03 = phi i32 [ %11, %10 ], [ %13, %12 ]
  br label %15

15:                                               ; preds = %22, %14
  %.0 = phi i32 [ 0, %14 ], [ %23, %22 ]
  %16 = icmp slt i32 %.0, 10
  br i1 %16, label %17, label %24

17:                                               ; preds = %15
  %18 = mul nsw i32 %.01, 7
  %19 = mul nsw i32 %18, %.02
  %20 = mul nsw i32 %.03, 3
  %21 = mul nsw i32 %.03, %.0
  br label %22

22:                                               ; preds = %17
  %23 = add nsw i32 %.0, 1
  br label %15, !llvm.loop !6

24:                                               ; preds = %15
  br label %25

25:                                               ; preds = %24
  %26 = add nsw i32 %.02, 1
  br label %5, !llvm.loop !8

27:                                               ; preds = %5
  ret i32 0
}

attributes #0 = { mustprogress noinline norecurse nounwind ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 4]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Homebrew clang version 20.1.3"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
