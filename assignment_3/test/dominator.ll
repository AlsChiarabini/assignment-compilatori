; ModuleID = 'dominator.ll'
source_filename = "dominator.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx15.0.0"

; Function Attrs: mustprogress noinline norecurse nounwind ssp uwtable
define noundef i32 @main() #0 {
  %1 = icmp sgt i32 5, 0
  br i1 %1, label %2, label %9

2:                                                ; preds = %0
  %3 = add nsw i32 5, 1
  %4 = icmp sgt i32 %3, 3
  br i1 %4, label %5, label %6

5:                                                ; preds = %2
  br label %7

6:                                                ; preds = %2
  br label %7

7:                                                ; preds = %6, %5
  %.01 = phi i32 [ 10, %5 ], [ 11, %6 ]
  %8 = sdiv i32 %.01, 2
  br label %11

9:                                                ; preds = %0
  %10 = mul nsw i32 5, -1
  br label %11

11:                                               ; preds = %9, %7
  %.1 = phi i32 [ %8, %7 ], [ %10, %9 ]
  br label %12

12:                                               ; preds = %17, %11
  %.02 = phi i32 [ 0, %11 ], [ %16, %17 ]
  %.0 = phi i32 [ 0, %11 ], [ %18, %17 ]
  %13 = icmp slt i32 %.0, 5
  br i1 %13, label %14, label %19

14:                                               ; preds = %12
  %15 = add nsw i32 10, 3
  %16 = add nsw i32 %.02, %15
  br label %17

17:                                               ; preds = %14
  %18 = add nsw i32 %.0, 1
  br label %12, !llvm.loop !6

19:                                               ; preds = %12
  %20 = mul nsw i32 %.1, %.1
  ret i32 %20
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
