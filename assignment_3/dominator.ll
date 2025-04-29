; ModuleID = 'dominator.ll'
source_filename = "dominator.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #0 {
entry:
  %1 = icmp sgt i32 5, 0
  br i1 %1, label %C, label %B

C:                                                ; preds = %entry
  %3 = add nsw i32 5, 1
  %4 = icmp sgt i32 %3, 3
  br i1 %4, label %D, label %E

D:                                                ; preds = %C
  br label %F

E:                                                ; preds = %C
  br label %F

F:                                                ; preds = %E, %D
  %.0 = phi i32 [ 10, %D ], [ 11, %E ]
  %8 = sdiv i32 %.0, 2
  br label %G

B:                                                ; preds = %entry
  %10 = mul nsw i32 5, -1
  br label %G

G:                                                ; preds = %B, %F
  %.1 = phi i32 [ %8, %F ], [ %10, %B ]
  %12 = mul nsw i32 %.1, %.1
  ret i32 %12
}

attributes #0 = { mustprogress noinline norecurse nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Debian clang version 19.1.4 (1~deb12u1)"}

