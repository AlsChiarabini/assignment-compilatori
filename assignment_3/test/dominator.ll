; ModuleID = 'dominator.ll'
source_filename = "dominator.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx15.0.0"

; Function Attrs: mustprogress noinline norecurse nounwind ssp uwtable
define noundef i32 @main() #0 {
  br label %1

1:                                                ; preds = %13, %0
  %.02 = phi i32 [ 0, %0 ], [ %.1, %13 ]
  %.01 = phi i32 [ 1, %0 ], [ %12, %13 ]
  %.0 = phi i32 [ 0, %0 ], [ %14, %13 ]
  %2 = icmp slt i32 %.0, 100
  br i1 %2, label %3, label %15

3:                                                ; preds = %1
  %4 = add nsw i32 3, 5
  %5 = add nsw i32 %4, 1
  %6 = mul nsw i32 %5, 2
  %7 = srem i32 %.0, 2
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %9, label %11

9:                                                ; preds = %3
  %10 = add nsw i32 %6, %.01
  br label %11

11:                                               ; preds = %9, %3
  %.1 = phi i32 [ %10, %9 ], [ %.02, %3 ]
  %12 = add nsw i32 %.1, %.0
  br label %13

13:                                               ; preds = %11
  %14 = add nsw i32 %.0, 1
  br label %1, !llvm.loop !6

15:                                               ; preds = %1
  ret i32 %.01
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
