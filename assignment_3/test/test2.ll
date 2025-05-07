; ModuleID = 'test2.ll'
source_filename = "test2.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx15.0.0"

; Function Attrs: mustprogress noinline norecurse nounwind ssp uwtable
define noundef i32 @main() #0 {
  %1 = icmp sgt i32 5, 0
  br i1 %1, label %2, label %3

2:                                                ; preds = %0
  br label %4

3:                                                ; preds = %0
  br label %4

4:                                                ; preds = %3, %2
  %.01 = phi i32 [ 1, %2 ], [ 2, %3 ]
  br label %5

5:                                                ; preds = %7, %4
  %.02 = phi i32 [ 3, %4 ], [ %9, %7 ]
  %.0 = phi i32 [ 0, %4 ], [ %10, %7 ]
  %6 = icmp slt i32 %.0, 10
  br i1 %6, label %7, label %11

7:                                                ; preds = %5
  %8 = mul nsw i32 %.01, 3
  %9 = add nsw i32 %.02, %8
  %10 = add nsw i32 %.0, 1
  br label %5, !llvm.loop !6

11:                                               ; preds = %5
  ret i32 %.02
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
